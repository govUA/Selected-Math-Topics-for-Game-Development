#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "json.hpp"
using json = nlohmann::json;

const int WIDTH = 1000;
const int HEIGHT = 1000;
const int SPOT_RADIUS = 5;

struct Point {
    double x, y;
    SDL_Color color;
};

std::vector<Point> loadPoints() {
    std::string filename;
    std::cout << "Enter the name of the JSON source file:\n";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << std::endl;
        return {};
    }

    srand(time(nullptr));

    json j;
    file >> j;

    std::vector<Point> points;
    for (const auto &spot : j["spots"]) {
        Point p;
        p.x = spot["x"];
        p.y = spot["y"];
        p.color = {
                static_cast<Uint8>(rand() % 256),
                static_cast<Uint8>(rand() % 256),
                static_cast<Uint8>(rand() % 256),
                255
        };
        points.push_back(p);
    }

    return points;
}

float euclideanDist(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float manhattanDist(double x1, double y1, double x2, double y2) {
    return std::abs(x2 - x1) + std::abs(y2 - y1);
}

float chebyshevDist(double x1, double y1, double x2, double y2) {
    return std::max(std::abs(x2 - x1), std::abs(y2 - y1));
}

void drawSpot(SDL_Surface *surface, int centerX, int centerY, SDL_Color color) {
    Uint32 pixelColor = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
    Uint32 *pixels = static_cast<Uint32 *>(surface->pixels);

    for (int y = -SPOT_RADIUS; y <= SPOT_RADIUS; ++y) {
        for (int x = -SPOT_RADIUS; x <= SPOT_RADIUS; ++x) {
            if (x*x + y*y <= SPOT_RADIUS*SPOT_RADIUS) {
                int drawX = centerX + x;
                int drawY = centerY + y;

                if (drawX >= 0 && drawX < WIDTH && drawY >= 0 && drawY < HEIGHT) {
                    pixels[drawY * WIDTH + drawX] = pixelColor;
                }
            }
        }
    }
}

void generateVoronoiImage(const std::vector<Point> &points,
                          const std::string &filename,
                          float (*distanceFunc)(double, double, double, double),
                          bool showSpots) {
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, SDL_PIXELFORMAT_RGBA32);

    Uint32 *pixels = static_cast<Uint32 *>(surface->pixels);

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            double px = static_cast<double>(x);
            double py = static_cast<double>(y);
            float minDist = 1e9;
            SDL_Color bestColor = {0, 0, 0, 255};

            for (const auto &p: points) {
                float dist = distanceFunc(px, py, p.x, p.y);
                if (dist < minDist) {
                    minDist = dist;
                    bestColor = p.color;
                }
            }

            Uint32 pixelColor = SDL_MapRGBA(surface->format,
                                            bestColor.r, bestColor.g, bestColor.b, bestColor.a);
            pixels[y * WIDTH + x] = pixelColor;
        }
    }

    if (showSpots) {
        SDL_Color spotColor = {0, 0, 0, 255};
        for (const auto &p: points) {
            drawSpot(surface, static_cast<int>(p.x), static_cast<int>(p.y), spotColor);
        }
    }

    IMG_SavePNG(surface, filename.c_str());
    SDL_FreeSurface(surface);
}

bool loop(std::vector<Point> points) {
    static bool showSpots = false;

    std::cout << "Choose distance for Voronoi diagram:\n"
                 "1. Euclidean\n"
                 "2. Manhattan\n"
                 "3. Chebyshev\n"
                 "4. Choose a different point set\n"
                 "5. Toggle spot display (currently " << (showSpots ? "ON" : "OFF") << ")\n"
                 "6. Exit\n";
    int choice;
    std::cin >> choice;
    bool success = true;
    switch (choice) {
        case 1:
            generateVoronoiImage(points, "voronoi_euclidean.png", euclideanDist, showSpots);
            break;
        case 2:
            generateVoronoiImage(points, "voronoi_manhattan.png", manhattanDist, showSpots);
            break;
        case 3:
            generateVoronoiImage(points, "voronoi_chebyshev.png", chebyshevDist, showSpots);
            break;
        case 4:
            points = loadPoints();
            break;
        case 5:
            showSpots = !showSpots;
            std::cout << "Spot display is now " << (showSpots ? "ON" : "OFF") << std::endl;
            break;
        case 6:
            std::cout << "Quitting...\n";
            return false;
        default:
            success = 0;
            std::cout << "Unknown choice. Try again.\n";
            break;
    }

    if (success) std::cout << "Done!" << std::endl;
    return loop(points);
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "SDL init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    while (loop(loadPoints()));
    IMG_Quit();
    SDL_Quit();
    return 0;
}
