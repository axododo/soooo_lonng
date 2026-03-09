#include "so_long.h"

#include "MLX42/includes/mlx.h"


void key_hook(int key, void *param)
{
    t_env *env;

    env = (t_env *)param;
    if (key == 41)
    {
        mlx_destroy_window(env->mlx, env->win);
        mlx_destroy_context(env->mlx);
    }
}

int main(void)
{
    t_env env;

    mlx_context mlx = mlx_init();
    env.mlx = mlx;

    mlx_window_create_info info = { 0 };

    info.title = "Hello World!";
    info.width = map->width*TILE;
    info.height = map->height*TILE;
    mlx_window win = mlx_new_window(mlx, &info);
    env.win = win;
    mlx_on_event(mlx, win, MLX_KEYDOWN, key_hook, &env);
    mlx_loop(mlx);
    mlx_destroy_window(mlx, win);
    mlx_destroy_context(mlx);
}
