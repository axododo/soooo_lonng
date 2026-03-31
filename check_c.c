/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguilber <mguilber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 11:47:57 by mguilber          #+#    #+#             */
/*   Updated: 2026/03/31 17:54:05 by mguilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	verif_w(int y, int x, t_map *map)
{
	if (y == 0 || y == map->height - 1 || x == 0 || x == map->width - 2)
		if (map->grid[y][x] != '1')
			return (0);
	if (map->grid[y][x] == 'P')
		map->p++;
	else if (map->grid[y][x] == 'E')
	{
		map->ex = x;
		map->ey = y;
		map->e++;
	}
	else if (map->grid[y][x] == 'C')
		map->collectable++;
	else if (map->grid[y][x] != '0' && map->grid[y][x] != '1')
		return (0);
	return (1);
}

int	check_chars(t_map *map)
{
	int	y;
	int	x;

	map->e = 0;
	map->p = 0;
	map->collectable = 0;
	map->collected = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width - 1)
		{
			if (!verif_w(y, x, map))
				return (0);
			if (map->grid[y][x + 1] == '\n')
				map->grid[y][x + 1] = '\0';
			x++;
		}
		y++;
	}
	if (map->collectable < 1 || map->p != 1 || map->e != 1)
		return (0);
	return (1);
}

int	verif_flood(t_map *map, char **tgrid)
{
	int	x;
	int	y;
	int	ok_exit;

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
	if (ok_exit == 1)
		return (1);
	return (0);
}
