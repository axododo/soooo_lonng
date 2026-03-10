#include "MLX42/includes/mlx.h"
#include "so_long.h"

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

int32_t	main(int argc, char **argv)
{
	t_env					env;
	mlx_window_create_info	info;

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
