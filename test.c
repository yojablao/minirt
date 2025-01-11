#include "minilibx_linux/mlx.h"
// void sigsegv_handler(int sig)
// {
//     printf("Caught segmentation fault\n");
//     exit(1);
// }
int main()
{
    void *mlx;
    void *win;
    // signal(SIGSEGV, sigsegv_handler);
    mlx = mlx_init();
    win = mlx_new_window(mlx, 640, 480, "Test MLX");
    mlx_loop(mlx);
    return (0);
}