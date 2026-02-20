#include "so_long.h"
#define WIDTH 800
#define HEIGHT 600




int32_t main(void)
{
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
}
