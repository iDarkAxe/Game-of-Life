#ifndef LIFE_H
# define LIFE_H

#define PRINT_DOLLAR_WRAPPING_MAP 1

// extern char **map;
extern char			**old_map;

// Hold the 'data' of the map
// extern char *map_data;
// extern char *old_map_data;
extern int			map_width;
extern int			map_height;
extern const char	aliveCell;
extern const char	deadCell;

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
