/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguilber <mguilber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 11:48:06 by mguilber          #+#    #+#             */
/*   Updated: 2026/03/27 18:04:16 by mguilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	init_image_walls(t_env *env, int *w, int *h)
{
	env->img_wall = mlx_new_image_from_file(env->mlx,
			"textures/wall.png", w, h);
	if (!env->img_wall)
		return (write(2, "Error\nCannot load wall.png\n", 27), 0);
	env->img_floor = mlx_new_image_from_file(env->mlx,
			"textures/floor.png", w, h);
	if (!env->img_floor)
		return (write(2, "Error\nCannot load floor.png\n", 28), 0);
	return (1);
}

static int	init_image_chars(t_env *env, int *w, int *h)
{
	env->img_collect = mlx_new_image_from_file(env->mlx,
			"textures/collect.png", w, h);
	if (!env->img_collect)
		return (write(2, "Error\nCannot load collect.png\n", 30), 0);
	env->img_exit = mlx_new_image_from_file(env->mlx,
			"textures/exit.png", w, h);
	if (!env->img_exit)
		return (write(2, "Error\nCannot load exit.png\n", 27), 0);
	env->img_player = mlx_new_image_from_file(env->mlx,
			"textures/player.png", w, h);
	if (!env->img_player)
		return (write(2, "Error\nCannot load player.png\n", 29), 0);
	env->img_win = mlx_new_image_from_file(env->mlx,
			"textures/win.png", w, h);
	if (!env->img_win)
		return (write(2, "Error\nCannot load win.png\n", 26), 0);
	return (1);
}

int	init_image(t_env *env)
{
	int	w;
	int	h;

	w = 16;
	h = 16;
	env->tile_w = w;
	env->tile_h = h;
	if (!init_image_walls(env, &w, &h))
	{
		mlx_destroy_context(env->mlx);
		free_map(env->map);
		return (0);
	}
	env->tile_w = w;
	env->tile_h = h;
	if (!init_image_chars(env, &w, &h))
	{
		mlx_destroy_image(env->mlx, env->img_wall);
		mlx_destroy_image(env->mlx, env->img_floor);
		mlx_destroy_context(env->mlx);
		free_map(env->map);
		return (0);
	}
	return (1);
}

void	window_hook(int event, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (event == 0)
	{
		free_map(env->map);
		clean(env);
		mlx_destroy_window(env->mlx, env->win);
		mlx_destroy_context(env->mlx);
		exit(0);
	}
}

void	clean(t_env *env)
{
	if (!env)
		return ;
	if (env->img_collect)
		mlx_destroy_image(env->mlx, env->img_collect);
	if (env->img_exit)
		mlx_destroy_image(env->mlx, env->img_exit);
	if (env->img_floor)
		mlx_destroy_image(env->mlx, env->img_floor);
	if (env->img_player)
		mlx_destroy_image(env->mlx, env->img_player);
	if (env->img_wall)
		mlx_destroy_image(env->mlx, env->img_wall);
	if (env->img_win)
		mlx_destroy_image(env->mlx, env->img_win);
	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env->mlx)
		mlx_destroy_context(env->mlx);
}
