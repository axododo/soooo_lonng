#include "MLX42/includes/mlx.h"
#include "so_long.h"

void	init_image(t_env *env)
{
	int	w;
	int	h;

	env->tile_w = w;
	env->tile_h = h;
	env->img_wall = mlx_new_image_from_file(env->mlx, "textures/wall.png", &w,
			&h);
	if (!env->img_wall)
	{
		write(2, "Error: cannot load wall.png\n", 28);
		return ;
	}
	env->tile_w = w;
	env->tile_h = h;
	env->img_floor = mlx_new_image_from_file(env->mlx, "textures/floor.png", &w,
			&h);
	if (!env->img_floor)
	{
		write(2, "Error: cannot load floor.png\n", 28);
		return ;
	}
	env->img_collect = mlx_new_image_from_file(env->mlx, "textures/collect.png",
			&w, &h);
	if (!env->img_collect)
	{
		write(2, "Error: cannot load collect.png\n", 28);
		return ;
	}
	env->img_exit = mlx_new_image_from_file(env->mlx, "textures/exit.png", &w,
			&h);
	if (!env->img_exit)
	{
		write(2, "Error: cannot load exit.png\n", 28);
		return ;
	}
	env->img_player = mlx_new_image_from_file(env->mlx, "textures/player.png",
			&w, &h);
	if (!env->img_player)
	{
		write(2, "Error: cannot load player.png\n", 28);
		return ;
	}
	env->img_win = mlx_new_image_from_file(env->mlx, "textures/win.png", &w,
			&h);
	if (!env->img_win)
	{
		write(2, "Error: cannot load win.png\n", 28);
		return ;
	}
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

// void findE(t_env *env)  {
//   int y = 0;
//   int x;
//   while (y < env->map->height)
//   {
//       x = 0;
//       while (x < env->map->width)
//       {
//         if(env->map->grid[y][x] == 'E')
//           env->map->grid[y][x] = 'X';
//         x++;
//       }
//     y++;
//   }
// }

void	win(t_env *env)
{
	int	win_w;
	int	win_h;
	int	img_w;
	int	img_h;

	win_w = env->map->width * env->tile_w;
	win_h = env->map->height * env->tile_h;
	img_w = 480;
	img_h = 320;
	env->stWin = 1;
	mlx_clear_window(env->mlx, env->win, (mlx_color){.rgba = 0x000000FF});
	mlx_put_image_to_window(env->mlx, env->win, env->img_win, (win_w - img_w)
			/ 2, (win_h - img_h) / 2);
}

void	move(t_env *env, int x, int y)
{
	int	i;
	int	j;

	i = env->map->px;
	j = env->map->py;
	x = x + i;
	y = y + j;
	if (env->map->grid[y][x] != '1')
	{
		if (env->map->grid[y][x] == 'C')
		{
			env->map->collected++;
			if (env->map->collected == env->map->collectable)
				env->map->grid[env->map->ey][env->map->ex] = 'X';
		}
		if (env->map->grid[y][x] == 'X')
		{
			win(env);
			return ;
		}
		env->map->grid[y][x] = 'P';
		env->map->grid[j][i] = '0';
		env->map->py = y;
		env->map->px = x;
		env->move++;
		ft_printf("move: %i\n", env->move);
		render_map(env);
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

void	free_map(t_map *map)
{
	int	y;

	y = 0;
	if (!map)
		return ;
	while (y < map->height)
		free(map->grid[y++]);
	free(map->grid);
	free(map);
}

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
	if (key == 26 && env->stWin == 0)
		move(env, 0, -1);
	if (key == 22 && env->stWin == 0)
		move(env, 0, 1);
	if (key == 7 && env->stWin == 0)
		move(env, 1, 0);
	if (key == 4 && env->stWin == 0)
		move(env, -1, 0);
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

int32_t	main(int argc, char **argv)
{
	t_env					env;
	mlx_window_create_info	info;

	info = {0};
	env.stWin = 0;
	env.move = 0;
	env.map = load_map(argv[1]);
	if (!env.map)
	{
		free_map(env.map);
		return (write(2, "Error: load_map\n", 16), 1);
	}
	if (!check_chars(env.map))
	{
		free_map(env.map);
		return (write(2, "Error: invalid map\n", 20), 1);
	}
	if (!check_path(env.map))
	{
		free_map(env.map);
		return (write(2, "Error: no valid path\n", 21), 1);
	}
	find_player(env.map);
	env.mlx = mlx_init();
	if (!env.mlx)
		return (write(2, "Error: mlx_init\n", 16), 1);
	init_image(&env);
	info.title = "so_long";
	info.width = env.map->width * env.tile_w;
	info.height = env.map->height * env.tile_h;
	env.win = mlx_new_window(env.mlx, &info);
	if (!env.win)
	{
		mlx_destroy_context(env.mlx);
		return (write(2, "Error: mlx_new_window\n", 22), 1);
	}
	render_map(&env);
	mlx_on_event(env.mlx, env.win, MLX_KEYDOWN, key_hook, &env);
	mlx_on_event(env.mlx, env.win, MLX_WINDOW_EVENT, window_hook, &env);
	mlx_loop(env.mlx);
	free_map(env.map);
	clean(&env);
	mlx_destroy_window(env.mlx, env.win);
	mlx_destroy_context(env.mlx);
	return (0);
}
