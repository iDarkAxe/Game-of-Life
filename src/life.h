#ifndef LIFE_H
# define LIFE_H

// Game init
int		loadGameParams(int width, int height, int iterations);
int		loadMapFromFile(const char *filename);
int		loadMap(void);


// Game logic
int		runGame(void);
int		countNeighbors(int x, int y);
int		isCoordValid(int x, int y);

// Game utils
void	freeGame(void);
void	printGame(void);
int		verifyRun(int retOfRun, int iterations);

#endif // LIFE_H
