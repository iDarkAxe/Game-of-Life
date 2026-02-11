
// Functions : atoi, read, putchar, malloc, calloc, realloc, free, putchar
// prototype : ./life width height iterations

// if argc == 2, argv[2] is the name of the file containing informations.
// if argc == 3, argv[2] is the name of the file containing informations and argv[3] is the number of iterations.
// if argc == 4, argv[2] and argv[3] are the width and height of the grid, respectively. argv[4] is the number of iterations.

// w a s d -> move the pen up, left, bottom, and right.
// x -> lift or lower the pen in order to start or stop drawing.

#include <stdio.h>
#include <stdlib.h>
#include "life.h"

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("Usage: %s width height iterations\n", argv[0]);
		return 1;
	}
	if (argc == 2)
		loadMap(argv[1]);
	int iterations = 0;
	if (argc == 4)
	{
		int width = atoi(argv[1]);
		int height = atoi(argv[2]);
		iterations = atoi(argv[3]);
		if (width <= 0 || height <= 0 || iterations < 0)
		{
			printf("Width and height must be positive integers, and iterations must be a non-negative integer.\n");
			return 1;
		}
		printf("Width: %d, Height: %d, Iterations: %d\n", width, height, iterations);
		if (loadGameParams(width, height) != 0)
		{
			freeGame();
			printf("Failed to load the game.\n");
			return 1;
		}
		loadMap(NULL);
	}
	int ret = runGame(iterations);
	if (ret == -1)
		printf("Failed to run the game.\n");
	else if (ret != iterations)
		printf("Failed to run the game, only %d/%d iterations completed.\n", ret, iterations);
	freeGame();
	return ret;
}
