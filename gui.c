#include "so_long.h"

int32_t main(int argc, char **argv)
{
    t_map *map;
    mlx_t* mlx;

mlx = mlx_init(WIDTH, HEIGHT, "Test MLX42", true);
if (!mlx)
{
    puts(mlx_strerror(mlx_errno));
    return (EXIT_FAILURE);
}

mlx_loop(mlx);

mlx_terminate(mlx);
return (EXIT_SUCCESS);
    return (0);
}

