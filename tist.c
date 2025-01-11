#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h> 

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct s_point {
    int x, y, z;
} t_point;

void project_isometric(t_point p, int *x, int *y) {
    double angle = M_PI / 6; // 30 degrees in radians
    *x = (p.x - p.y) * cos(angle);
    *y = (p.x + p.y) * sin(angle) - p.z;
}

void draw_line(void *mlx, void *win, int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        mlx_pixel_put(mlx, win, x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void draw_z_axis(void *mlx, void *win) {
    t_point p_start = {0, 0, 0};  // Start of Z-axis
    t_point p_end = {0, 0, 100}; // End of Z-axis
    int x1, y1, x2, y2;

    // Project points to 2D
    project_isometric(p_start, &x1, &y1);
    project_isometric(p_end, &x2, &y2);

    // Adjust to window center
    x1 += WIN_WIDTH / 2;
    y1 += WIN_HEIGHT / 2;
    x2 += WIN_WIDTH / 2;
    y2 += WIN_HEIGHT / 2;

    // Draw Z-axis line
    draw_line(mlx, win, x1, y1, x2, y2, 0x00FF00); // Green line
}

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "3D Z-axis");

    draw_z_axis(mlx, win);

    mlx_loop(mlx);
    return 0;
}
