#include "so_long.h"

void	win_screen(t_env *env)
{
	int	win_w;
	int	win_h;
	int	img_w;
	int	img_h;

	win_w = env->map->width * env->tile_w;
	win_h = env->map->height * env->tile_h;
	img_w = 480;
	img_h = 320;
	env->stwin = 1;
	mlx_clear_window(env->mlx, env->win, (mlx_color){.rgba = 0x000000FF});
	mlx_put_image_to_window(env->mlx, env->win, env->img_win, (win_w - img_w)
		/ 2, (win_h - img_h) / 2);
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

void	move_player(t_env *env, int x, int y)
{
	int	i;
	int	j;

	i = env->map->px;
	j = env->map->py;
	x = x + i;
	y = y + j;
	if (env->map->grid[y][x] == '1')
		return ;
	if (env->map->grid[y][x] == 'C')
	{
		env->map->collected++;
		if (env->map->collected == env->map->collectable)
			env->map->grid[env->map->ey][env->map->ex] = 'X';
	}
	if (env->map->grid[y][x] == 'X')
	{
		win_screen(env);
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

size_t	ft_sstrlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
