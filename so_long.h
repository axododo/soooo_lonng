#include "MLX42/includes/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
//#include <MLX42/include/MLX42/MLX42.h>

typedef struct s_map {
  char **grid;
  int width;
  int height;
} t_map;

typedef struct s_env {
  mlx_context mlx;
  mlx_window win;
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
int find_player(t_map *map, int *py, int *px);
