/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguilber <mguilber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 11:48:36 by mguilber          #+#    #+#             */
/*   Updated: 2026/03/22 12:30:54 by mguilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	flood(char **grid, int y, int x, t_map *map)
{
	if (y < 0 || y >= map->height || x < 0
		|| x >= map->width)
		return ;
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	grid[y][x] = 'V';
	flood(grid, y - 1, x, map);
	flood(grid, y + 1, x, map);
	flood(grid, y, x - 1, map);
	flood(grid, y, x + 1, map);
}

int	free_tgrid(char **tgrid, int height)
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
	int		ok;
	char	**tgrid;

	tgrid = dup_grid(map);
	if (!tgrid)
		return (0);
	if (!find_player(map))
		return (free_tgrid(tgrid, map->height));
	flood(tgrid, map->py, map->px, map);
	ok = 0;
	ok = verif_flood(map, tgrid);
	if (!ok)
		return (0);
	free_tgrid(tgrid, map->height);
	return (1);
}
