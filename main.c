#include "so_long.h"


#define WIDTH 800
#define HEIGHT 600
int check_chars(t_map *map) {
    int p = 0;
    int e = 0;
    int c = 0;
    int y = 0;
    int x;

    while (y < map->height) {
        x = 0;
        while (x < map->width)  {
            if (y == 0 || y == map->height - 1
                || x == 0 || x == map->width - 1) {
                if (map->grid[y][x] != '1')
                    return (0);
            }
            if (map->grid[y][x] == 'P')
                p++;
            else if (map->grid[y][x] == 'E')
                e++;
            else if (map->grid[y][x] == 'C')
                c++;
            else if (map->grid[y][x] != '0' && map->grid[y][x] != '1')
                return (0);
            x++;
        }
        y++;
    }
    if (p != 1 || e != 1 || c < 1)
        return (0);
    return (1);
}



static size_t	ft_sstrlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int count_map(const char *path, int *height, int *width) {
  char *line;

  *height = 0;
  *width = 0;
  int fd = open(path, O_RDONLY);
  if(fd == -1)
    return (0);
  line = get_next_line(fd);
  *width = ft_sstrlen(line);
  while (line) {
    (*height)++;
    free(line);
    line = get_next_line(fd);
  }
  close(fd);
  return (1);
}

t_map *load_map(const char *path)
{
    int     height;
    int     width;
    int     i;
    int     fd;
    char    *line;
    t_map   *map;

    if (!count_map(path, &height, &width))
        return (NULL);
    map = malloc(sizeof(t_map));
    if (!map)
        return (NULL);
    map->height = height;
    map->width = width;
    map->grid = malloc(sizeof(char *) * map->height);
    if (!map->grid)
        return (free(map), NULL);
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (free(map->grid), free(map), NULL);
    i = 0;
    line = get_next_line(fd);
    while (line && i < map->height)
    {
        map->grid[i] = line;
        i++;
        line = get_next_line(fd);
    }
    close(fd);
    return (map);
}

int find_player(t_map *map, int *py, int *px)
{
    int y = 0;
    int x;

    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->grid[y][x] == 'P')
            {
                *py = y;
                *px = x;
                return (1);
            }
            x++;
        }
        y++;
    }
    return (0);
}

char **dup_grid(t_map *map) {
  char **copy;
  int y = 0;

  copy = malloc(sizeof(char *) * map->height);
  while(y < map->height) {
    copy[y] = ft_strdup(map->grid[y]);
    if (!copy[y]) {
            while (y > 0)
                free(copy[--y]);
            free(copy);
            return (NULL);
        }
    y++;
  }
  return(copy);
}

void flood(char **grid, int y, int x, int height, int width) {
  if (y < 0 || y >= height || x < 0 || x >= width)
        return;
  if (grid[y][x] == '1' || grid[y][x] == 'V')
        return;

  grid[y][x] = 'V';
  flood(grid, y - 1, x, height, width);
  flood(grid, y + 1, x, height, width);
  flood(grid, y, x - 1, height, width);
  flood(grid, y, x + 1, height, width);
}

int check_path(t_map *map)
{
    int   py;
    int   px;
    int   x;
    int   y;
    int   ok_exit;
    char **tGrid;

    tGrid = dup_grid(map);
    if (!tGrid)
        return (0);
    if (!find_player(map, &py, &px))
        return (0);
    flood(tGrid, py, px, map->height, map->width);

    ok_exit = 0;
    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (tGrid[y][x] == 'C')
            {
                int yy = 0;
                while (yy < map->height)
                    free(tGrid[yy++]);
                free(tGrid);
                return (0);
            }
            if (map->grid[y][x] == 'E' && tGrid[y][x] == 'V')
                ok_exit = 1;
            x++;
        }
        y++;
    }
    y = 0;
    while (y < map->height)
        free(tGrid[y++]);
    free(tGrid);
    if (!ok_exit)
        return (0);
    return (1);
}


// int32_t main(int argc, char **argv)
// {
//     t_map *map;
//     int    px;
//     int    py;
//
//     if (argc != 2)
//         return (write(2, "Error\n", 6), 1);
//     map = load_map(argv[1]);
//     if (!map)
//         return (write(2, "Error\n", 6), 1);
//     if (!check_chars(map))
//         return (write(2, "Error\n", 6), 1);
//     if (!find_player(map, &py, &px))
//         return (write(2, "Error\n", 6), 1);
//     printf("w = %d, h = %d\n", map->width, map->height);
//     printf("player at %d, %d\n", py, px);
//     if (!check_chars(map) || !check_path(map))
//     return (write(2, "Error\n", 6), 1);
//
//     return (0);
// }




// mlx_t* mlx;
//
// mlx = mlx_init(WIDTH, HEIGHT, "Test MLX42", true);
// if (!mlx)
// {
//     puts(mlx_strerror(mlx_errno));
//     return (EXIT_FAILURE);
// }
//
// mlx_loop(mlx);
//
// mlx_terminate(mlx);
// return (EXIT_SUCCESS);
