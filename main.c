#include "mlx.h"

int main(void)
{
    void    *mlx;
    void    *win;

    mlx = mlx_init();
    if (!mlx)
        return (1);
    win = mlx_new_window(mlx, 800, 600, "MLX Test");
    if (!win)
        return (1);
    mlx_loop(mlx);
    return (0);
}
