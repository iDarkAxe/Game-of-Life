#include <stdio.h>
#include "life.h"

// extern char **map;
extern char **old_map;

// Hold the 'data' of the map
// extern char *map_data;
// extern char *old_map_data;
extern int map_width;
extern int map_height;
extern const char aliveCell;
extern const char deadCell;

int verifyRun(int retOfRun, int iterations)
{
	if (retOfRun != iterations)
	{
		if (retOfRun == -1)
			printf("Failed to run the game.\n");
		else
			printf("Failed to run the game, only %d/%d iterations completed.\n", retOfRun, iterations);
		return 1;
	}
	return 0;
}

int isCoordValid(int x, int y)
{
	if (x < 0 || y < 0 || x >= map_width || y >= map_height)
		return (0);
	return (1);
}

void printGame()
{
	printf("Debut:\n");
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_width; j++)
			putchar(old_map[i][j]);
		putchar('$');
		putchar('\n');
	}
	printf("Fin\n");
}

int countNeighbors(int x, int y)
{
	int count = 0;

	if (x < 0 || y < 0)
		return (0);
	if (isCoordValid(x - 1, y - 1) && old_map[x - 1][y - 1] == aliveCell)
		count++;
	if (isCoordValid(x, y - 1) && old_map[x][y - 1] == aliveCell)
		count++;
	if (isCoordValid(x + 1, y - 1) && old_map[x + 1][y - 1] == aliveCell)
		count++;
	if (isCoordValid(x - 1, y) && old_map[x - 1][y] == aliveCell)
		count++;
	if (isCoordValid(x + 1, y) && old_map[x + 1][y] == aliveCell)
		count++;
	if (isCoordValid(x - 1, y + 1) && old_map[x - 1][y + 1] == aliveCell)
		count++;
	if (isCoordValid(x, y + 1) && old_map[x][y + 1] == aliveCell)
		count++;
	if (isCoordValid(x + 1, y + 1) && old_map[x + 1][y + 1] == aliveCell)
		count++;
	return (count);
}
