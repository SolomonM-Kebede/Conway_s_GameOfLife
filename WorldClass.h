#ifndef WORLDCLASS_H
#define WORLDCLASS_H

#include <vector>
#include <string>

class WorldClass {
private:
    int width{};
    int height{};
    std::vector<std::vector<bool>> current;
    std::vector<std::vector<bool>> previous;
    std::vector<std::vector<bool>> twoGenerationsAgo;

public:
    // Constructors
    WorldClass(int h, int w);
    explicit WorldClass(const std::string& filename);

    // Core methods
    void evolve();
    bool is_stable() const;
    void print() const;
    void save(const std::string& filename) const;
    void load(const std::string& filename);

    // Getters / Setters
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    bool getCell(int x, int y) const;
    void setCell(int x, int y, bool state);

private:
    int countNeighbors(int x, int y) const;
};

#endif