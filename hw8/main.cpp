#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>

const int WIDTH = 1000;
const int HEIGHT = 1000;

struct Point {
    int x, y;
    SDL_Color color;
};

std::vector<Point> loadPoints() {
    std::string filename;
    std::cout << "Enter the name of the source file:\n";
    std::cin >> filename;
    std::vector<Point> points;
    std::ifstream file(filename);
    int x, y;

    while (file >> x >> y) {
        Point p;
        p.x = x;
        p.y = y;
        p.color = {static_cast<Uint8>(rand() % 256),
                   static_cast<Uint8>(rand() % 256),
                   static_cast<Uint8>(rand() % 256),
                   255};
        points.push_back(p);
    }

    return points;
}

float euclideanDist(int x1, int y1, int x2, int y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float manhattanDist(int x1, int y1, int x2, int y2) {
    return std::abs(x2 - x1) + std::abs(y2 - y1);
}

float chebyshevDist(int x1, int y1, int x2, int y2) {
    return std::max(std::abs(x2 - x1), std::abs(y2 - y1));
}

void generateVoronoiImage(const std::vector<Point> &points,
                          const std::string &filename,
                          float (*distanceFunc)(int, int, int, int)) {
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, SDL_PIXELFORMAT_RGBA32);

    Uint32 *pixels = static_cast<Uint32 *>(surface->pixels);

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            float minDist = 1e9;
            SDL_Color bestColor = {0, 0, 0, 255};

            for (const auto &p: points) {
                float dist = distanceFunc(x, y, p.x, p.y);
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

    IMG_SavePNG(surface, filename.c_str());
    SDL_FreeSurface(surface);
}

bool loop(std::vector<Point> points) {
    std::cout << "Chose distance for Voronoi diagram:\n"
                 "1. Euclidian\n"
                 "2. Manhattan\n"
                 "3. Chebyshev\n"
                 "4. Chose a different point set\n"
                 "5. Exit\n";
    int choice;
    std::cin >> choice;
    bool success = true;
    switch (choice) {
        case 1:
            generateVoronoiImage(points, "voronoi_euclidean.png", euclideanDist);
            break;
        case 2:
            generateVoronoiImage(points, "voronoi_manhattan.png", manhattanDist);
            break;
        case 3:
            generateVoronoiImage(points, "voronoi_chebyshev.png", chebyshevDist);
            break;
        case 4:
            points = loadPoints();
            break;
        case 5:
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
