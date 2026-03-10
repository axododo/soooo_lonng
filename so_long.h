#include "MLX42/includes/mlx.h"
#include "printft/ft_printf.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			collected;
	int			collectable;
	int			px;
	int			py;
	int			ex;
	int			ey;
}				t_map;

typedef struct s_env
{
	mlx_context	mlx;
	mlx_window	win;
	t_map		*map;
	mlx_image	tile;
	int			tile_w;
	int			tile_h;
	mlx_image	img_wall;
	mlx_image	img_floor;
	mlx_image	img_collect;
	mlx_image	img_exit;
	mlx_image	img_player;
	mlx_image	img_win;
	int			stWin;
	int			move;
}				t_env;

int	check_chars(t_map *map);
int	count_map(const char *path, int *height, int *width);
t_map	*load_map(const char *path);
int	find_player(t_map *map);
char	**dup_grid(t_map *map);
void	flood(char **grid, int y, int x, int height, int width);
int	check_path(t_map *map);
int	init_image(t_env *env);
void	render_map(t_env *env);
void	window_hook(int event, void *param);
void	clean(t_env *env);
void	win(t_env *env);
void	move(t_env *env, int x, int y);
void	free_map(t_map *map);
void	key_hook(int key, void *param);

char			*get_next_line(int fd);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *src);
