#include "minilibx_linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

int main() {
    // Initialize MiniLibX
    void *mlx = mlx_init();
    if (!mlx) {
        fprintf(stderr, "Error: MiniLibX initialization failed\n");
        return 1;
    }

    // Create a window
    void *win = mlx_new_window(mlx, WIDTH, HEIGHT, "MiniLibX Window");
    if (!win) {
        fprintf(stderr, "Error: Window creation failed\n");
        mlx_destroy_display(mlx);
        return 1;
    }

    // Create an image
    void *img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img) {
        fprintf(stderr, "Error: Image creation failed\n");
        mlx_destroy_window(mlx, win);
        mlx_destroy_display(mlx);
        return 1;
    }

    // Get the image's pixel data
    char *data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

    // Draw to the image
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int color = 0xFF0000; // Red color
            *(int *)(data + y * size_line + x * (bpp / 8)) = color;
        }
    }

    // Put the image into the window
    mlx_put_image_to_window(mlx, win, img, 0, 0);

    // Start the MiniLibX loop
    mlx_loop(mlx);

    // Clean up (this will never be reached in this example)
    mlx_destroy_image(mlx, img);
    mlx_destroy_window(mlx, win);
    mlx_destroy_display(mlx);
    return 0;
}