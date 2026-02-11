#ifndef LIFE_H
#define LIFE_H

int loadGameParams(int width, int height);
int loadMap(char *filename);
int runGame(int iterations);
int verifyRun(int retOfRun, int iterations);
void freeGame();
void printGame();

#endif //LIFE_H
