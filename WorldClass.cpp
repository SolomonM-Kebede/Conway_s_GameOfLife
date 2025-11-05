#include "WorldClass.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

WorldClass::WorldClass(const int h, const int w)
    : width(w), height(h),
      current(h, std::vector<bool>(w, false)),
      previous(h, std::vector<bool>(w, false)),
      twoGenerationsAgo(h, std::vector<bool>(w, false)) {
}

WorldClass::WorldClass(const std::string& filename) {
    load(filename);
}

void WorldClass::evolve() {
    // Create next generation grid (same size as current)
    std::vector<std::vector<bool>> next = current;

    // Compute next generation from current
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int neighbors = countNeighbors(x, y);
            if (current[y][x]) {
                next[y][x] = (neighbors == 2 || neighbors == 3);
            } else {
                next[y][x] = (neighbors == 3);
            }
        }
    }

    // Shift generations after computing the new one
    twoGenerationsAgo = previous;
    previous = current;
    current = next;
}

int WorldClass::countNeighbors(const int x, const int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            const int nx = (x + dx + width) % width;
            const int ny = (y + dy + height) % height;
            if (current[ny][nx]) count++;
        }
    }
    return count;
}

bool WorldClass::is_stable() const {
    // still life
    if (current == previous)
        return true;
    // period-2 oscillator
    if (current == twoGenerationsAgo)
        return true;
    // otherwise unstable
    return false;
}

void WorldClass::print() const {
    // Move cursor to top-left and clear screen
    std::cout << "\033[2J\033[H";
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (current[y][x]) {
                // Alive cell: green blocks
                std::cout << "\033[1m\033[32m\u2593\u2593\033[0m";
            } else {
                // Dead cell: gray blocks
                std::cout << "\033[1m\033[90m\u2591\u2591\033[0m";
            }
        }
        std::cout << '\n';
    }
    std::cout.flush();
}

void WorldClass::save(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot save file");

    file << height << " " << width << "\n";
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            file << current[y][x] << " ";
        }
        file << "\n";
    }
    file.close();
}

void WorldClass::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file");

    file >> height >> width;
    current.assign(height, std::vector<bool>(width, false));
    previous.assign(height, std::vector<bool>(width, false));
    twoGenerationsAgo.assign(height, std::vector<bool>(width, false));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int val;
            file >> val;
            current[y][x] = (val != 0);
        }
    }
    file.close();
}

bool WorldClass::getCell(int x, int y) const {
    return current[y % height][x % width];
}

void WorldClass::setCell(int x, int y, bool state) {
    current[y % height][x % width] = state;
}


