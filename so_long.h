#include <stdio.h>
#include <stdlib.h>
#include <MLX42/include/MLX42/MLX42.h>

typedef struct s_map {
  char **grid;
  int width;
  int height;
} t_map;


char	*get_next_line(int fd);
