//
// Created by Yevheniya CHUFISTOVA on 2019-03-15.
//

#include "fdf.h"

void draw_line(t_map *map, t_coord c0, t_coord c1)
{
    printf("here6\n");
    t_point xy;

    xy.x = c0.x;
    ft_printf("x: %d ", xy.x);
    xy.y = c0.y;
    ft_printf("y: %d \n", xy.y);
    if (fabs(c1.y - c0.y) > fabs(c1.x - c0.x))
    {
        ft_printf("here10\n");
        while (c0.y > c1.y ? xy.y >= c1.y : xy.y <= c1.y) //вставляем по х
        {
            xy.x = ((xy.y - c0.y) / (c0.y - c1.y) * (c0.x - c1.x) + c0.x);
            map->image[xy.x + (xy.y * WIN_X)] = 0x8fcbc;
            c1.y > c0.y ? xy.y++ : xy.y--;
        }
        printf("here11\n");
    }
    else
    {
        ft_printf("here12\n");
        while (c0.x > c1.x ? xy.x >= c1.x : xy.x <= c1.x) //вставляем по у
        {
            xy.y = ((xy.x - c0.x) / (c0.x - c1.x) * (c0.y - c1.y) + c0.y);
            ft_printf("lool2\n");
            map->image[xy.x + (xy.y * WIN_X)] = 0x8fcbc;
            ft_printf("lool3\n");
            c1.x > c0.x ? xy.x++ : xy.x--;
            ft_printf("lool4\n");
        }
        ft_printf("here13\n");
    }
    ft_printf("here8\n");
}

void draw_net(t_map *map)
{
    int i;
    int j;

    i = -1;

    while (++i < map->size.y)
    {
        ft_printf("here5\n");
        j = -1;
        while (++j < map->size.x - 1)
            draw_line(map, map->coords[i][j], map->coords[i][j + 1]);
    }
    i = -1;
    while (++i < map->size.y - 1)
    {
        ft_printf("here7\n");
        j = -1;
        while (++j < map->size.x)
            draw_line(map, map->coords[i][j], map->coords[i + 1][j]);
    }
    ft_printf("here9\n");
}

void draw_map(t_map *map)
{
//    xyz_in_xy(map, 15);
//    move_map_to_centre(map);
    draw_net(map);
    ft_printf("here4\n");
    mlx_put_image_to_window(map->mlx, map->window, map->img, 0, 0);
    mlx_hook(map->window, 2, 0, bonuses, map);
//    system("leaks fdf");

}