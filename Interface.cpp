#include "Interface.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <random>


/**
 * Command line interface to enable user interaction with cellular automaton.
 */
void Interface::CLI() {
    std::cout << "Conway’s Game of Life CLI started.\n";
    std::cout << "Type 'help' for commands, 'exit' to quit.\n";

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "exit") break;
        if (line == "help") {
            std::cout << "Available commands:\n"
                      << "create <h> <w>\n load <file>\n save <file>\n"
                      << "print <0|1>\n delay <ms>\n stability <0|1>\n"
                      << "run <n>\n set <x> <y> <0|1>\n set <p> <0|1>\n"
                      << "get <x> <y>\n get <p>\n"
                      << "glider <x> <y>\n toad <x> <y>\n beacon <x> <y>\n methuselah <x> <y>\n"
                      << "random <n>\nexit\n";
            continue;
        }
        executeCommand(line);
    }
}

void Interface::executeCommand(const std::string& line) {
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;

    if (cmd == "create") {
        int h, w;
        iss >> h >> w;
        cmdCreate(h, w);
    } else if (cmd == "load") {
        std::string file; iss >> file; cmdLoad(file);
    } else if (cmd == "save") {
        std::string file; iss >> file; cmdSave(file);
    } else if (cmd == "print") {
        int e; iss >> e; cmdPrint(e);
    } else if (cmd == "delay") {
        int ms; iss >> ms; cmdDelay(ms);
    } else if (cmd == "stability") {
        int e; iss >> e; cmdStability(e);
    } else if (cmd == "run") {
        int n; iss >> n; cmdRun(n);
    } else if (cmd == "set") {
        std::vector<int> vals; int v;
        while (iss >> v) vals.push_back(v);
        if (vals.size() == 2) cmdSet1D(vals[0], vals[1]);
        else if (vals.size() == 3) cmdSet(vals[0], vals[1], vals[2]);
    } else if (cmd == "get") {
        std::vector<int> vals; int v;
        while (iss >> v) vals.push_back(v);
        if (vals.size() == 1) cmdGet1D(vals[0]);
        else if (vals.size() == 2) cmdGet(vals[0], vals[1]);
    } else if (cmd == "glider") {
        int x, y; iss >> x >> y; cmdGlider(x, y);
    } else if (cmd == "toad") {
        int x, y; iss >> x >> y; cmdToad(x, y);
    } else if (cmd == "beacon") {
        int x, y; iss >> x >> y; cmdBeacon(x, y);
    } else if (cmd == "methuselah") {
        int x, y; iss >> x >> y; cmdMethuselah(x, y);
    } else if (cmd == "random") {
        int n; iss >> n; cmdRandom(n);
    } else {
        std::cout << "Unknown command.\n";
    }
}

// Command Implementations

void Interface::cmdCreate(int h, int w) {
    world = std::make_unique<WorldClass>(h, w);
    std::cout << "Created world " << h << "x" << w << "\n";
}

void Interface::cmdLoad(const std::string& filename) {
    world = std::make_unique<WorldClass>(filename);
    std::cout << "Loaded world from " << filename << "\n";
}

void Interface::cmdSave(const std::string& filename) const {
    if (!world) return;
    world->save(filename);
    std::cout << "Saved world to " << filename << "\n";
}

void Interface::cmdPrint(const int enabled) {
    printEnabled = enabled;
    std::cout << "Printing " << (enabled ? "enabled" : "disabled") << "\n";
}

void Interface::cmdDelay(int ms) {
    delayMs = ms;
    std::cout << "Delay set to " << ms << " ms\n";
}

void Interface::cmdStability(int enabled) {
    stabilityCheckEnabled = enabled;
    std::cout << "Stability check " << (enabled ? "enabled" : "disabled") << "\n";

}

void Interface::cmdRun(const int generations) {
    if (!world) { std::cout << "No world loaded.\n"; return; }

    // Enter alternate screen for clean animation
    if (printEnabled) std::cout << "\033[?1049h";

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < generations; ++i) {
        world->evolve();
        if (printEnabled) {
            world->print();
            sleepFor(delayMs);
        }
        if (stabilityCheckEnabled && world->is_stable()) {
            std::cout << "World reached stability at generation " << i << "\n";
            break;
        }
    }
    const auto end = std::chrono::steady_clock::now();

    // Exit alternate screen
    if (printEnabled) std::cout << "\033[?1049l";

    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Run completed in " << duration.count() << " ms\n";
}

void Interface::cmdSet(const int x, const int y, const int state) {
    if (!world) return;
    world->setCell(x, y, state);
}

void Interface::cmdSet1D(const int p, const int state) {
    if (!world) return;
    const int w = world->getWidth();
    const int x = p % w;
    const int y = p / w;
    world->setCell(x, y, state);
}

void Interface::cmdGet(const int x, const int y) {
    if (!world) return;
    std::cout << world->getCell(x, y) << "\n";
}

void Interface::cmdGet1D(const int p) {
    if (!world) return;
    int w = world->getWidth();
    int x = p % w;
    int y = p / w;
    std::cout << world->getCell(x, y) << "\n";
}

// ---- Patterns ----

void Interface::addPattern(const std::vector<std::pair<int,int>>& pattern, const int x, const int y) const {
    if (!world) return;
    for (auto [dx, dy] : pattern)
        world->setCell(x + dx, y + dy, true);
}

void Interface::cmdGlider(const int x, const int y) {
    addPattern({{0,1},{1,2},{2,0},{2,1},{2,2}}, x, y);
}

void Interface::cmdToad(const int x, const int y) {
    addPattern({{1,0},{2,0},{3,0},{0,1},{1,1},{2,1}}, x, y);
}

void Interface::cmdBeacon(const int x, const int y) {
    addPattern({{0,0},{1,0},{0,1},{2,2},{3,2},{3,3}}, x, y);
}

void Interface::cmdMethuselah(const int x, const int y) {
    addPattern({{1,0},{2,0},{0,1},{1,1},{1,2}}, x, y);
}

void Interface::cmdRandom(const int n) {
    if (!world) return;
    std::vector<void (Interface::*)(int,int)> patterns = {
        &Interface::cmdGlider, &Interface::cmdToad, &Interface::cmdBeacon, &Interface::cmdMethuselah
    };
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> px(0, world->getWidth() - 1);
    std::uniform_int_distribution<int> py(0, world->getHeight() - 1);
    std::uniform_int_distribution<int> pick(0, (int)patterns.size() - 1);

    for (int i = 0; i < n; ++i)
        (this->*patterns[pick(rng)])(px(rng), py(rng));
}

void Interface::sleepFor(const int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void Interface::autoRun(const std::string& filename, int generations) {
    // Disable printing and stability check for benchmarking
    printEnabled = false;
    stabilityCheckEnabled = false;
    delayMs = 0;

    // Manually load the world file (same logic as cmdLoad)
    world = std::make_unique<WorldClass>(filename);
    std::cout << "Loaded world from " << filename << "\n";

    // Run evolution loop for n generations
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < generations; ++i)
        world->evolve();

    auto end = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Run completed in " << duration.count() << " ms ("
              << generations << " generations)\n";
}


void Interface::autoRunWithSize(const std::string& filename, int width, int height, int generations) {
    // Create world
    world = std::make_unique<WorldClass>(height, width);
    world->load(filename);

    // Disable printing & stability
    printEnabled = false;
    stabilityCheckEnabled = false;



    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < generations; ++i)
        world->evolve();
    auto end = std::chrono::steady_clock::now();

    double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << height << "," << width << ","  <<generations<< "," << duration << "ms\n";
}
