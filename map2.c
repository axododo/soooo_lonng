#include "so_long.h"

int	find_player(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == 'P')
			{
				map->px = x;
				map->py = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

char	**dup_grid(t_map *map)
{
	char	**copy;
	int		y;

	y = 0;
	copy = malloc(sizeof(char *) * map->height);
	if (!copy)
		return (NULL);
	while (y < map->height)
	{
		copy[y] = ft_strdup(map->grid[y]);
		if (!copy[y])
		{
			while (y > 0)
				free(copy[--y]);
			free(copy);
			return (NULL);
		}
		y++;
	}
	return (copy);
}

void	flood(char **grid, int y, int x, int height, int width)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return ;
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	grid[y][x] = 'V';
	flood(grid, y - 1, x, height, width);
	flood(grid, y + 1, x, height, width);
	flood(grid, y, x - 1, height, width);
	flood(grid, y, x + 1, height, width);
}

static int	free_tgrid(char **tgrid, int height)
{
	int	y;

	y = 0;
	while (y < height)
		free(tgrid[y++]);
	free(tgrid);
	return (0);
}

int	check_path(t_map *map)
{
	int		x;
	int		y;
	int		ok_exit;
	char	**tgrid;

	tgrid = dup_grid(map);
	if (!tgrid)
		return (0);
	if (!find_player(map))
		return (free_tgrid(tgrid, map->height));
	flood(tgrid, map->py, map->px, map->height, map->width);
	ok_exit = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (tgrid[y][x] == 'C')
				return (free_tgrid(tgrid, map->height));
			if (map->grid[y][x] == 'E' && tgrid[y][x] == 'V')
				ok_exit = 1;
			x++;
		}
		y++;
	}
	free_tgrid(tgrid, map->height);
	if (!ok_exit)
		return (0);
	return (1);
}
