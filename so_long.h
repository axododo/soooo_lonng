/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguilber <mguilber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 11:48:49 by mguilber          #+#    #+#             */
/*   Updated: 2026/03/29 19:55:22 by mguilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/includes/mlx.h"
# include "printft/ft_printf.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

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
	int			e;
	int			p;
}				t_map;

typedef struct s_env
{
	mlx_context	mlx;
	mlx_window	win;
	t_map		*map;
	int			tile_w;
	int			tile_h;
	mlx_image	img_wall;
	mlx_image	img_floor;
	mlx_image	img_collect;
	mlx_image	img_exit;
	mlx_image	img_player;
	mlx_image	img_win;
	int			stwin;
	int			move;
}				t_env;

int				check_chars(t_map *map);
int				count_map(const char *path, int *height, int *width);
t_map			*load_map(const char *path);
int				find_player(t_map *map);
char			**dup_grid(t_map *map);
void			flood(char **grid, int y, int x, t_map *map);
int				check_path(t_map *map);
int				init_image(t_env *env);
void			render_map(t_env *env);
void			window_hook(int event, void *param);
void			clean(t_env *env);
void			win_screen(t_env *env);
void			move_player(t_env *env, int x, int y);
void			free_map(t_map *map);
void			key_hook(int key, void *param);
int				check_extension(const char *path);
int				check_rect(const char *path, int width);
int				fill_grid(t_map *map, int fd);
int				verif_flood(t_map *map, char **tgrid);
int				free_tgrid(char **tgrid, int height);
void			put_image(char c, t_env *env, int x, int y);
size_t			ft_sstrlen(const char *str);
char			*get_next_line(int fd);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *src);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
