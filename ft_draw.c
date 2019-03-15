//
// Created by Yevheniya CHUFISTOVA on 2019-03-15.
//

#include "fdf.h"

void draw_line(t_map *map, t_coord c0, t_coord c1)
{
//    printf("here4\n");
    t_point xy;

    xy.x = c0.x;
//    printf("x: %d ", xy.x);
    xy.y = c0.y;
//    printf("y: %d \n", xy.y);
    if (fabs(c1.y - c0.y) > fabs(c1.x - c0.x)) {
//        ft_printf("here8\n");
        while (c0.y > c1.y ? xy.y >= c1.y : xy.y <= c1.y) //вставляем по х
        {
            xy.x = ((xy.y - c0.y) / (c0.y - c1.y) * (c0.x - c1.x) + c0.x);
            map->image[xy.x + (xy.y * WIN_X)] = 0x8fcbc;
            c1.y > c0.y ? xy.y++ : xy.y--;
        }
//        printf("here5\n");
    }
    else
    {
        while (c0.x > c1.x ? xy.x >= c1.x : xy.x <= c1.x) //вставляем по у
        {
            xy.y = ((xy.x - c0.x) / (c0.x - c1.x) * (c0.y - c1.y) + c0.y);
            map->image[xy.x + (xy.y * WIN_X)] = 0x8fcbc;
            c1.x > c0.x ? xy.x++ : xy.x--;
        }
//        printf("here6\n");
    }
}

void draw_net(t_map *map)
{
    t_point	xy;

    xy.y = -1;
//    ft_printf("here91\n");
    while (++xy.y < map->size.y)
    {
        xy.x = -1;
        while (++xy.x < map->size.x - 1)
        {
            draw_line(map, map->coords[xy.y][xy.x], map->coords[xy.y][xy.x + 1]);
        }
    }
    xy.y = -1;
    while (++xy.y < map->size.y - 1)
    {
        xy.x = -1;
        while (++xy.x < map->size.x)
        {
            draw_line(map, map->coords[xy.y][xy.x], map->coords[xy.y + 1][xy.x]);
        }
    }
}

void draw_map(t_map *map)
{
//    xyz_in_xy(map, 15);
//    move_map_to_centre(map);
    draw_net(map);
//    ft_printf("here3\n");
    mlx_put_image_to_window(map->mlx, map->window, map->img, 0, 0);
    mlx_hook(map->window, 2, 0, bonuses, map);
//    system("leaks fdf");

}