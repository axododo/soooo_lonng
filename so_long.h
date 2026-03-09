#include "MLX42/includes/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "printft/ft_printf.h"
//#include <MLX42/include/MLX42/MLX42.h>

typedef struct s_map {
  char **grid;
  int width;
  int height;
  int collected;
  int collectable;
  int px;
  int py;
} t_map;

typedef struct s_env {
  mlx_context mlx;
  mlx_window win;
  t_map *map;
  mlx_image tile;
  int         tile_w;
  int         tile_h;
  mlx_image   img_wall;
  mlx_image   img_floor;
  mlx_image   img_collect;
  mlx_image   img_exit;
  mlx_image   img_player;
  mlx_image   img_win;
  int stWin;
  int move;
} t_env;

size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
char	*ft_strdup(const char *src);
int check_chars(t_map *map);
t_map *load_map(const char *path);
int count_map(const char *path, int *height, int *width);
char **dup_grid(t_map *map);
void flood(char **grid, int y, int x, int height, int width);
int check_path(t_map *map);
int find_player(t_map *map);
