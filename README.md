This is the code to simulate the famous Conway’s Game of Life which provides a beginner-friendly platform to explore arrays, loops, and conditional
logic in C++. 
- Ths file consits of separate header and source codes for two basic classes. 
- WorldClass provide the rule of the game (the game's world)
- Interface class givens a plat form to play the game. 
There are three methods to run the code in main class , one is custom based in which any one can create its own grid and set the rules for themselves including where the living cell start and stability and print capabilties on or off future and run as much as generation anyone want.
to compile without optimization and with debuging : g++ -std=c++17 O0 -g -o game main.cpp WorldClass.cpp Interface.cpp or use clang++ environment.
