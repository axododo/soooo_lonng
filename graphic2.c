/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguilber <mguilber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 11:48:10 by mguilber          #+#    #+#             */
/*   Updated: 2026/03/22 11:48:11 by mguilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_map(t_env *env)
{
	int		y;
	int		x;
	char	c;

	mlx_clear_window(env->mlx, env->win, (mlx_color){.rgba = 0xC16868FF});
	y = 0;
	while (y < env->map->height)
	{
		x = 0;
		while (x < env->map->width)
		{
			c = env->map->grid[y][x];
			put_image(c, env, x, y);
			x++;
		}
		y++;
	}
}

void	put_image(char c, t_env *env, int x, int y)
{
	if (c == 'P')
		mlx_put_image_to_window(env->mlx, env->win, env->img_player, x
			* env->tile_w, y * env->tile_h);
	else if (c == 'X')
		mlx_put_image_to_window(env->mlx, env->win, env->img_exit, x
			* env->tile_w, y * env->tile_h);
	else if (c == 'C')
		mlx_put_image_to_window(env->mlx, env->win, env->img_collect, x
			* env->tile_w, y * env->tile_h);
	else if (c == '1')
		mlx_put_image_to_window(env->mlx, env->win, env->img_wall, x
			* env->tile_w, y * env->tile_h);
	else if (c == '0' || c == 'E')
		mlx_put_image_to_window(env->mlx, env->win, env->img_floor, x
			* env->tile_w, y * env->tile_h);
}
