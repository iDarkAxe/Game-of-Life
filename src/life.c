#include "life.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

#define BUFFER_SIZE 100

// Hold the 'structure' of the map
static char **map = NULL;
static char **old_map = NULL;

// Hold the 'data' of the map
static char *map_data = NULL;
static char *old_map_data = NULL;
static int map_width = -1;
static int map_height = -1;
static const char aliveCell = '0';
static const char deadCell = ' ';

int loadGameParams(int width, int height)
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
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			old_map[j][i] = deadCell;
	}
	map_width = width;
	map_height = height;
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
	printGame();
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

int isUpdateValid(int x, int y)
{
	if (x < 0 || y < 0 || x > map_width || y > map_height)
		return (0);
	return (1);
}

int interpret_sequence(char *buffer)
{
	if (!buffer)
		return (1);
	char penWriting = 0;
	int x;
	int y;
	for(size_t index = 0; buffer[index] != '\0'; index++)
	{
		switch (buffer[index])
		{
			case 'x':
				penWriting = !penWriting;
				break;
			case 's':
				if (isUpdateValid(x, y + 1))
					y++;
				break;
			case 'w':
				if (isUpdateValid(x, y - 1))
					y--;
				break;
			case 'd':
				if (isUpdateValid(x + 1, y))
					x++;
				break;
			case 'a':
				if (isUpdateValid(x - 1, y))
					x--;
				break;
			default:
				break; //ignore any other key
		}
		if (penWriting)
			old_map[x][y] = aliveCell;
	}
	return (0);
}

/**
 * @brief Load the map
 * if filename isn't NULL, it will try to open the file and read from it.
 * It will read from stdin if not precised.
 * 
 * @param[in] filename filename of map
 * @return int 
 */
int loadMap(char *filename)
{
	int fd;
	char	buffer[BUFFER_SIZE];
	ssize_t ret;

	if (filename)
	{
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			return (1);
	}
	else
		fd = 0; //read on stdin
	while (1)
	{
		ret = read(fd, buffer, BUFFER_SIZE - 0);
		if (ret < 0 || ret == 0)
			break;
		buffer[ret] = '\0';
		if (interpret_sequence(buffer) != 0)
			break;
	}
	if (fd != 0)
		close(fd);
	return (0);
}

void printGame()
{
	printf("Debut:\n");
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_width; j++)
			putchar(old_map[j][i]);
		putchar('\n');
	}
	printf("Fin\n");
}
