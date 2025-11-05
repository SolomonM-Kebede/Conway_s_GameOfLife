#ifndef INTERFACE_H
#define INTERFACE_H

#include "WorldClass.h"
#include <string>
#include <memory>
#include <unordered_map>

class Interface {
private:
    std::unique_ptr<WorldClass> world;
    bool printEnabled = true;
    bool stabilityCheckEnabled = false;
    int delayMs = 100;

public:
    Interface() = default;

    void CLI();
    void executeCommand(const std::string& line);




    void autoRun(const std::string &filename, int generations);

    void autoRunWithSize(const std::string &filename, int width, int height, int generations);

private:
    // command handlers
    void cmdCreate(int h, int w);
    void cmdLoad(const std::string& filename);
    void cmdSave(const std::string& filename) const;
    void cmdPrint(int enabled);
    void cmdDelay(int ms);
    void cmdStability(int enabled);
    void cmdRun(int generations);
    void cmdSet(int x, int y, int state);
    void cmdSet1D(int p, int state);
    void cmdGet(int x, int y);
    void cmdGet1D(int p);
    void cmdGlider(int x, int y);
    void cmdToad(int x, int y);
    void cmdBeacon(int x, int y);
    void cmdMethuselah(int x, int y);
    void cmdRandom(int n);

    void addPattern(const std::vector<std::pair<int,int>>& pattern, int x, int y) const;

    static void sleepFor(int ms);


};

#endif