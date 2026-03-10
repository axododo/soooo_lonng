
#include "so_long.h"


int	init_image(t_env *env)
{
  int	w = 16;
  int	h = 16;

	env->tile_w = w;
	env->tile_h = h;
	env->img_wall = mlx_new_image_from_file(env->mlx, "textures/wall.png", &w,
			&h);
	if (!env->img_wall)
	{
		write(2, "Error: cannot load wall.png\n", 28);
		return (0);
	}
	env->tile_w = w;
	env->tile_h = h;
	env->img_floor = mlx_new_image_from_file(env->mlx, "textures/floor.png", &w,
			&h);
	if (!env->img_floor)
	{
		write(2, "Error: cannot load floor.png\n", 28);
		return (0);
	}
	env->img_collect = mlx_new_image_from_file(env->mlx, "textures/collect.png",
			&w, &h);
	if (!env->img_collect)
	{
		write(2, "Error: cannot load collect.png\n", 28);
		return (0);
	}
	env->img_exit = mlx_new_image_from_file(env->mlx, "textures/exit.png", &w,
			&h);
	if (!env->img_exit)
	{
		write(2, "Error: cannot load exit.png\n", 28);
		return (0);
	}
	env->img_player = mlx_new_image_from_file(env->mlx, "textures/player.png",
			&w, &h);
	if (!env->img_player)
	{
		write(2, "Error: cannot load player.png\n", 28);
		return (0);
	}
	env->img_win = mlx_new_image_from_file(env->mlx, "textures/win.png", &w,
			&h);
	if (!env->img_win)
	{
		write(2, "Error: cannot load win.png\n", 28);
		return (0);
	}
	return (1);
}

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
			if (c == 'P')
				mlx_put_image_to_window(env->mlx, env->win, env->img_player, x
						* env->tile_w, y * env->tile_h);
			else if (c == 'X')
			{
				mlx_put_image_to_window(env->mlx, env->win, env->img_exit, x
						* env->tile_w, y * env->tile_h);
			}
			else if (c == 'C')
				mlx_put_image_to_window(env->mlx, env->win, env->img_collect, x
						* env->tile_w, y * env->tile_h);
			else if (c == '1')
			{
				mlx_put_image_to_window(env->mlx, env->win, env->img_wall, x
						* env->tile_w, y * env->tile_h);
			}
			else if (c == '0' || c == 'E')
				mlx_put_image_to_window(env->mlx, env->win, env->img_floor, x
						* env->tile_w, y * env->tile_h);
			x++;
		}
		y++;
	}
}


void	window_hook(int event, void *param)
{
	t_env	env;

	if (event == 0)
	{
		free_map(env.map);
		clean(&env);
		mlx_destroy_window(env.mlx, env.win);
		mlx_destroy_context(env.mlx);
		exit(0);
	}
}

void	clean(t_env *env)
{
	mlx_destroy_image(env->mlx, env->img_collect);
	mlx_destroy_image(env->mlx, env->img_exit);
	mlx_destroy_image(env->mlx, env->img_floor);
	mlx_destroy_image(env->mlx, env->img_player);
	mlx_destroy_image(env->mlx, env->img_wall);
	mlx_destroy_image(env->mlx, env->img_win);
}
