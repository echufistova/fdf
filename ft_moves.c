//
// Created by Yevheniya CHUFISTOVA on 2019-03-15.
//

#include "fdf.h"

void move_map_to_centre(t_map *map)
{
    t_point ij;
    t_point xy;
    t_coord coord;

    ij.y = -1;
    xy.y = map->size.y * 20 / 2;
    xy.x = map->size.x * 20 / 2;
    while (++ij.y < map->size.y)
    {
        ij.x = -1;
        while (++ij.x < map->size.x)
        {
            coord.x = map->coords[ij.y][ij.x].x;
            map->coords[ij.y][ij.x].x = coord.x - xy.x + WIN_X / 2;
            coord.y = map->coords[ij.y][ij.x].y;
            map->coords[ij.y][ij.x].y = coord.y - xy.y + WIN_Y / 2;
        }
    }
}

void movexy(t_map *map, int key)
{
    if (key == 123)
        recount_map_xyz(map, 123, -10);
    else if (key == 124)
        recount_map_xyz(map, 124, 10);
    else if (key == 125)
        recount_map_xyz(map, 125, 10);
    else if (key == 126)
        recount_map_xyz(map, 126, -10);
    else if (key == 0)
        xyz_in_xy(map, map->angle++);
//    else if (key == 13)
//    else if (key == 13)
//    else if (key == 13)
    ft_bzero(map->image, 4 * WIN_X * WIN_Y);
//    mlx_clear_window(map->mlx, map->window);
//    move_map_to_centre(map);
//    ft_printf("hello1\n");
    draw_map(map);
//    ft_printf("hello2\n");
}

int bonuses(int key, void *map)
{
    if (key == 53)
        exit(1);
    else if (key >= 123 && key <= 126)
    {
        movexy(map, key);
    }
    return (1);
}