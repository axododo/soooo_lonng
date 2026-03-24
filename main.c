/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguilber <mguilber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 11:48:26 by mguilber          #+#    #+#             */
/*   Updated: 2026/03/24 17:21:10 by mguilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	key_hook(int key, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (key == 41)
	{
		free_map(env->map);
		clean(env);
		mlx_destroy_window(env->mlx, env->win);
		mlx_destroy_context(env->mlx);
		exit(0);
	}
	if (key == 26 && env->stwin == 0)
		move_player(env, 0, -1);
	if (key == 22 && env->stwin == 0)
		move_player(env, 0, 1);
	if (key == 7 && env->stwin == 0)
		move_player(env, 1, 0);
	if (key == 4 && env->stwin == 0)
		move_player(env, -1, 0);
}

static int	init_map(t_env *env, const char *path)
{
	if (!check_extension(path))
		return (write(2, "Error\nMap must have .ber extension\n", 35), 0);
	env->map = load_map(path);
	if (!env->map)
		return (write(2, "Error\nCannot load map\n", 22), 0);
	if (!check_chars(env->map))
	{
		free_map(env->map);
		return (write(2, "Error\nInvalid map characters or borders\n", 40), 0);
	}
	if (!check_path(env->map))
	{
		free_map(env->map);
		return (write(2, "Error\nNo valid path in map\n", 27), 0);
	}
	if (!find_player(env->map))
	{
		free_map(env->map);
		return (write(2, "Error\nCannot find player\n", 25), 0);
	}
	return (1);
}

static int	init_window(t_env *env, mlx_window_create_info *info)
{
	env->win = mlx_new_window(env->mlx, info);
	if (!env->win)
	{
		mlx_destroy_context(env->mlx);
		return (write(2, "Error\nmlx_new_window failed\n", 28), 1);
	}
	render_map(env);
	mlx_on_event(env->mlx, env->win, MLX_KEYDOWN, key_hook, env);
	mlx_on_event(env->mlx, env->win, MLX_WINDOW_EVENT, window_hook, env);
	mlx_loop(env->mlx);
	free_map(env->map);
	clean(env);
	mlx_destroy_window(env->mlx, env->win);
	mlx_destroy_context(env->mlx);
	return (0);
}

int32_t	main(int argc, char **argv)
{
	t_env					env;
	mlx_window_create_info	info;

	if (argc != 2)
		return (write(2, "Error\nUsage: ./so_long <map.ber>\n", 33), 1);
	env.stwin = 0;
	env.move = 0;
	if (!init_map(&env, argv[1]))
		return (1);
	env.mlx = mlx_init();
	if (!env.mlx)
		return (write(2, "Error\nmlx_init failed\n", 22), 1);
	if (!init_image(&env))
		return (1);
	info.title = "so_long";
	info.width = env.map->width * env.tile_w;
	info.height = env.map->height * env.tile_h;
	info.is_resizable = 0;
	info.is_fullscreen = 0;
	if (init_window(&env, &info))
		return (1);
	return (0);
}
