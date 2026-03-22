#include "so_long.h"

int	verif_w(int y, int x, t_map *map)
{
	int	verif;

	verif = 0;
	if (y == 0 || y == map->height - 1 || x == 0 || x == map->width - 1)
		if (map->grid[y][x] != '1')
			return (verif);
	if (map->grid[y][x] == 'P')
	{
		verif++;
	}
	else if (map->grid[y][x] == 'E')
	{
		map->ex = x;
		map->ey = y;
		verif++;
	}
	else if (map->grid[y][x] == 'C')
		map->collectable++;
	else if (map->grid[y][x] != '0' && map->grid[y][x] != '1')
		return (0);
	return (verif);
}

int	check_chars(t_map *map)
{
	int	y;
	int	x;
	int	verif;

	verif = 0;
	map->collectable = 0;
	map->collected = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width - 1)
		{
			verif += verif_w(y, x, map);
			x++;
		}
		y++;
	}
	if (verif != 2 || map->collectable < 1)
		return (0);
	return (1);
}
