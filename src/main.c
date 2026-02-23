
// Functions : atoi, read, putchar, malloc, calloc, realloc, free, putchar
// prototype : ./life width height iterations

// if argc == 2, argv[2] is the name of the file containing informations.
// if argc == 3,
// argv[2] is the name of the file containing informations and argv[3] is the number of iterations.
// if argc == 4, argv[2] and argv[3] are the width and height of the grid,
// respectively. argv[4] is the number of iterations.

// w a s d -> move the pen up, left, bottom, and right.
// x -> lift or lower the pen in order to start or stop drawing.

#include "life.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	int	ret;

	if (argc != 4)
	{
		printf("Usage: %s width height iterations\n", argv[0]);
		return (1);
	}
	// TODO implement the possibility to load a map from a file
	// else if (argc == 2)
	// 	loadMapFromFile(argv[1]);
	else if (argc == 4)
	{
		if (loadGameParams(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])) != 0)
		{
			freeGame();
			printf("Failed to load the game.\n");
			return (1);
		}
		loadMap();
	}
	ret = runGame();
	freeGame();
	return (ret);
}
