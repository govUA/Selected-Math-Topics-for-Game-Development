#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "json.hpp"

using json = nlohmann::json;

WORD WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
WORD CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE;
WORD YELLOW = FOREGROUND_RED | FOREGROUND_GREEN;
WORD PURPLE = FOREGROUND_RED | FOREGROUND_BLUE;
WORD RED = FOREGROUND_RED | FOREGROUND_INTENSITY;
WORD GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
WORD GRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

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

    std::cout << "Reading file content...\n";

    json j;
    file >> j;

    std::vector<Point> points;
    std::cout << "Mapping points...\n";
    for (const auto &spot: j["spots"]) {
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
            if (x * x + y * y <= SPOT_RADIUS * SPOT_RADIUS) {
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
                          bool showSpots,
                          const std::string &quote) {
    std::cout << "Creating surface...\n";
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, SDL_PIXELFORMAT_RGBA32);

    Uint32 *pixels = static_cast<Uint32 *>(surface->pixels);

    std::cout << quote;
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
        std::cout << "Putting spots...\n";
        SDL_Color spotColor = {0, 0, 0, 255};
        for (const auto &p: points) {
            drawSpot(surface, static_cast<int>(p.x), static_cast<int>(p.y), spotColor);
        }
    }

    IMG_SavePNG(surface, filename.c_str());
    SDL_FreeSurface(surface);
}

void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void colorString(const std::string &_s, const std::string &s, const std::string &s_, WORD color) {
    std::cout << _s;
    setConsoleColor(color);
    std::cout << s;
    setConsoleColor(WHITE);
    std::cout << s_;
}

bool loop(std::vector<Point> points) {
    static bool showSpots = false;

    std::cout << "Choose distance for Voronoi diagram:\n";
    colorString("1. ", "Euclidean ◎", "\n", CYAN);
    colorString("2. ", "Manhattan ▣", "\n", YELLOW);
    colorString("3. ", "Chebyshev ◈", "\n", PURPLE);
    std::cout << "4. Choose a different point set ⇄\n";
    colorString("5. Toggle spot display (currently ", (showSpots ? "ON" : "OFF"), ") ◉\n", (showSpots ? GREEN : GRAY));
    std::cout << "6. Exit ⌂\n";

    int choice;
    std::cin >> choice;
    bool success = true;

    switch (choice) {
        case 1:
            generateVoronoiImage(points, "voronoi_euclidean.png", euclideanDist, showSpots, "When in Alexandria...\n");
            break;
        case 2:
            generateVoronoiImage(points, "voronoi_manhattan.png", manhattanDist, showSpots,
                                 "It's hip to be square...\n");
            break;
        case 3:
            generateVoronoiImage(points, "voronoi_chebyshev.png", chebyshevDist, showSpots,
                                 "All directions are equal...\n");
            break;
        case 4:
            points = loadPoints();
            break;
        case 5:
            showSpots = !showSpots;
            colorString("Spot display is now ", (showSpots ? "ON" : "OFF"), "\n", (showSpots ? GREEN : WHITE));
            break;
        case 6:
            std::cout << "Quitting...\n";
            return false;
        default:
            success = 0;
            colorString("", "Unknown choice.", "\nTry again.\n", RED);
            break;
    }

    if (success) {
        colorString("", "Done!", "\n", GREEN);
    }
    return loop(points);
}

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "SDL init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    while (loop(loadPoints()));
    IMG_Quit();
    SDL_Quit();
    return 0;
}
