#include <stdlib.h>
#include <stdio.h>

// Hold the 'structure' of the map
static char **map = NULL;
static char **old_map = NULL;

// Hold the 'data' of the map
static char *map_data = NULL;
static char *old_map_data = NULL;

int loadGame(int width, int height)
{
	if (width <= 0 || height <= 0 || width * height < 1)
	{
		printf("Width and height must be positive integers, and iterations must be a non-negative integer.\n");
		return 1;
	}
	// Allouer les tableaux de pointeurs
	map = malloc(height * sizeof(char *));
	if (map == NULL)
		return 1;
	old_map = malloc(height * sizeof(char *));
	if (old_map == NULL)
		return 1;

	// Allouer toutes les données en un seul bloc contigu
	map_data = malloc(height * width * sizeof(char));
	if (map_data == NULL)
		return 1;
	old_map_data = malloc(height * width * sizeof(char));
	if (old_map_data == NULL)
		return 1;
	// Initialiser les pointeurs de lignes
	for (int i = 0; i < height; i++)
	{
		map[i] = &map_data[i * width];
		old_map[i] = &old_map_data[i * width];
	}
	return 0;
}

void freeGame()
{
	void *pointers[] = {map, old_map, map_data, old_map_data};
	for(size_t i = 0; i < sizeof(pointers) / sizeof(pointers[0]); i++)
	{
		if (pointers[i] != NULL)
			free(pointers[i]);
	}
}

int runGame(int iterations)
{
	if (iterations < 0)
	{
		printf("Iterations must be a non-negative integer.\n");
		return -1;
	}
	for(int i = 0; i < iterations; i++)
	{
		;
	}
	return iterations;
}

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
