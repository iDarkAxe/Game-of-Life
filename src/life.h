#ifndef LIFE_H
#define LIFE_H



int loadGameParams(int width, int height);
int loadMap(const char *filename);
int runGame(int iterations);
int verifyRun(int retOfRun, int iterations);
void freeGame();
void printGame();
int isCoordValid(int x, int y);
int countNeighbors(int x, int y);

#endif //LIFE_H
