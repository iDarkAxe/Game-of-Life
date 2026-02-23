#include "life.h"
#include <fcntl.h> // for open
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for close

#define BUFFER_SIZE 100
#define PRINT_EACH_ITERATIONS 0

#define PRINT_INVALID_LETTERS 0
#define BLOCK_INVALID_LETTERS 0

#define USE_PRINTF 1

// Hold the 'structure' of the map
static char	**map = NULL;
char		**old_map = NULL;

// Hold the 'data' of the map
static char	*map_data = NULL;
static char	*old_map_data = NULL;
int			map_width = -1;
int			map_height = -1;
static int	target_iterations = -1;
const char	aliveCell = '0';
const char	deadCell = ' ';

static int	interpret_sequence(char *buffer);

int	loadGameParams(int width, int height, int iterations)
{
	int map_chunk = width * height;
	if (width <= 0 || height <= 0 || map_chunk < 1 || map_chunk < width || map_chunk < height || iterations < 0)
	{
		if (USE_PRINTF)
			printf("Width and height must be positive integers, \
				and iterations must be a non-negative integer.\n");
		return (1);
	}
	// Allouer les tableaux de pointeurs
	map = malloc((size_t)height * sizeof(char *));
	if (map == NULL)
		return (1);
	old_map = malloc((size_t)height * sizeof(char *));
	if (old_map == NULL)
		return (1);
	// Allouer toutes les données en un seul bloc contigu
	map_data = malloc((size_t)map_chunk * sizeof(char));
	if (map_data == NULL)
		return (1);
	old_map_data = malloc((size_t)map_chunk * sizeof(char));
	if (old_map_data == NULL)
		return (1);
	// Initialiser les pointeurs de lignes
	for (int i = 0; i < height; i++)
	{
		map[i] = &map_data[i * width];
		old_map[i] = &old_map_data[i * width];
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			old_map[i][j] = deadCell;
	}
	map_width = width;
	map_height = height;
	target_iterations = iterations;
	return (0);
}

int	loadMapFromFile(const char *filename)
{
	int	fd;

	fd = 0;
	(void)fd;
	(void)filename;
	return (0);
}

void	freeGame(void)
{
	void	*pointers[] = {map, old_map, map_data, old_map_data};

	for (size_t i = 0; i < sizeof(pointers) / sizeof(pointers[0]); i++)
	{
		if (pointers[i] != NULL)
			free(pointers[i]);
	}
}

int	runGame(void)
{

	if (target_iterations < 0)
	{
		if (USE_PRINTF)
			printf("Iterations must be a non-negative integer.\n");
		return (-1);
	}
	int		it = 0;
	
	for (; it < target_iterations; it++)
	{
		for (int y = 0; y < map_height; y++)
		{
			for (int x = 0; x < map_width; x++)
			{
				int nbNeighbors = countNeighbors(x, y);
				if ((old_map[y][x] == aliveCell && nbNeighbors == 2)
					|| nbNeighbors == 3)
					map[y][x] = aliveCell;
				else
					map[y][x] = deadCell;
			}
		}
		char	**temp = map;
		map = old_map;
		old_map = temp;
		if (PRINT_EACH_ITERATIONS)
			printGame();
	}
	if (!PRINT_EACH_ITERATIONS || (target_iterations == 0
			&& PRINT_EACH_ITERATIONS))
		printGame();
	return (verifyRun(it, target_iterations));
}

int	interpret_sequence(char *buffer)
{
	if (!buffer)
		return (1);
	char	penWriting = 0;
	int		x = 0, y = 0;

	for (size_t index = 0; buffer[index] != '\0'; index++)
	{
		switch (buffer[index])
		{
		case 'x':
			penWriting = !penWriting;
			break ;
		case 's':
			if (isCoordValid(x, y + 1))
				y++;
			break ;
		case 'w':
			if (isCoordValid(x, y - 1))
				y--;
			break ;
		case 'd':
			if (isCoordValid(x + 1, y))
				x++;
			break ;
		case 'a':
			if (isCoordValid(x - 1, y))
				x--;
			break ;
		default:
			if (USE_PRINTF && PRINT_INVALID_LETTERS)
				printf("'%c'<- is invalid\n", buffer[index]);
			if (BLOCK_INVALID_LETTERS)
				return (1);
			break ; // ignore any other key
		}
		if (penWriting)
			old_map[y][x] = aliveCell;
	}
	return (0);
}

/**
 * @brief Load the map
 * It will read from stdin.
 *
 * @return int
 */
int	loadMap(void)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	ret;

	int map_chunk = map_width * map_height;
	if (map_width <= 0 || map_height <= 0 || map_chunk < 1
		|| map_chunk < map_width || map_chunk < map_height
		|| target_iterations < 0)
		return (1);
	while (1)
	{
		ret = read(0, buffer, BUFFER_SIZE - 0);
		if (ret < 0 || ret == 0)
			break ;
		buffer[ret] = '\0';
		if (interpret_sequence(buffer) != 0)
			break ;
	}
	return (0);
}
