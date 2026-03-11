#include "so_long.h"

static size_t	ft_sstrlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_extension(const char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".ber", 4) == 0);
}

int	check_chars(t_map *map)
{
	int	p;
	int	e;
	int	y;
	int	x;

	p = 0;
	e = 0;
	y = 0;
	map->collectable = 0;
	map->collected = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width - 1)
		{
			if (y == 0 || y == map->height - 1 || x == 0 || x == map->width - 1)
				if (map->grid[y][x] != '1')
					return (0);
			if (map->grid[y][x] == 'P')
				p++;
			else if (map->grid[y][x] == 'E')
			{
				e++;
				map->ex = x;
				map->ey = y;
			}
			else if (map->grid[y][x] == 'C')
				map->collectable++;
			else if (map->grid[y][x] != '0' && map->grid[y][x] != '1')
				return (0);
			x++;
		}
		y++;
	}
	if (p != 1 || e != 1 || map->collectable < 1)
		return (0);
	return (1);
}

int	check_rect(const char *path, int width)
{
	char	*line;
	int		fd;
	int		ok;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	ok = 1;
	line = get_next_line(fd);
	while (line)
	{
		if ((int)ft_sstrlen(line) != width)
			ok = 0;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (ok);
}

int	count_map(const char *path, int *height, int *width)
{
	char	*line;
	int		fd;

	*height = 0;
	*width = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 0);
	*width = ft_sstrlen(line);
	while (line)
	{
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	fill_grid(t_map *map, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line && i < map->height)
	{
		map->grid[i] = line;
		i++;
		line = get_next_line(fd);
	}
	return (1);
}

t_map	*load_map(const char *path)
{
	int		height;
	int		width;
	int		fd;
	t_map	*map;

	if (!count_map(path, &height, &width))
		return (NULL);
	if (!check_rect(path, width))
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
	fill_grid(map, fd);
	close(fd);
	return (map);
}
