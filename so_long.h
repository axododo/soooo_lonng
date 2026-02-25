#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <MLX42/include/MLX42/MLX42.h>

typedef struct s_map {
  char **grid;
  int width;
  int height;
} t_map;

size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
char	*ft_strdup(const char *src);
