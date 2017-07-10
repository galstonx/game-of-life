# game-of-life
Conway's Game of Life in C++

This is a simple implentation of Conway's Game of Life

https://en.wikipedia.org/wiki/Conway's_Game_of_Life

The main program is life.cpp and the binary for the program is 

life

It works on Linux. It requires the ncurses library. The program can be compiled using

g++ -c GameController.cpp
g++ -c LifeClasses.cpp
g++ -c IOClasses.cpp
g++ -static life.cpp GameController.o IOClasses.o LifeClasses.o -o life -lncurses -ltinfo -lgpm


The basic idea is:

0) the "game" is a cellular automata
1) the game consists of a world or universe, this is implemented in the Universe class
2) the universe contains cells (implemented in the Cell class)
3) cells have a state
4) cells are linked to neighbors as determined by the geometry of the universe
5) the states of the cells evolve according to rules (depending on the type of cell)
6) the fun is in watching the patterns that emerge!
