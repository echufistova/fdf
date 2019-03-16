//
// Created by Yevheniya CHUFISTOVA on 2019-03-15.
//

#include "fdf.h"

void move_map_to_centre(t_map *map, int n, int p1, int p2)
{
    t_point ij;
    t_coord coord;

    ij.y = -1;
//    ft_printf("map size.x - %d, map size.y %d\n", map->size.x * 10, map->size.y * 10);
    while (++ij.y < map->size.y)
    {
        ij.x = -1;
        while (++ij.x < map->size.x)
        {
//            printf("coord.x : %f, coord.y: %f\n", map->coords[ij.y][ij.x].x, map->coords[ij.y][ij.x].y);
            coord.x = map->coords[ij.y][ij.x].x;
            coord.y = map->coords[ij.y][ij.x].y;
//            ft_printf("coord.x : %d, coord.y: %d\n", coord.x, coord.y);
            if (n == 0)
            {
                map->coords[ij.y][ij.x].x = coord.x - map->size.x * 5;
                map->coords[ij.y][ij.x].y = coord.y - map->size.y * 5;
                printf("n: %d, x: %f, y: %f\n", n, map->coords[ij.y][ij.x].x, map->coords[ij.y][ij.x].y);
            }
            if (n == 1)
            {
                printf("n: %d, x: %f, y: %f\n", n, map->coords[ij.y][ij.x].x, map->coords[ij.y][ij.x].y);
                map->coords[ij.y][ij.x].x = coord.x + p1;
                map->coords[ij.y][ij.x].y = coord.y + p2;
            }
        }
    }
}

void rotate_x(t_map *map, double angle)
{
    int i;
    int j;
    t_coord xy;

    i = -1;
    while (++i < map->size.y)
    {
        j = -1;
        while (++j < map->size.x)
        {
            xy.y = map->coords[i][j].y;
            xy.z = map->coords[i][j].z;
            map->coords[i][j].y = xy.y * cos(angle) + xy.z * sin(angle);
            map->coords[i][j].z = -xy.y * sin(angle) + xy.z * cos(angle);
        }
    }
}

void rotate_y(t_map *map, double angle)
{
    int i;
    int j;
    t_coord xy;


    i = -1;
    while (++i < map->size.y)
    {
        j = -1;
        while (++j < map->size.x)
        {
            xy.x = map->coords[i][j].x;
            xy.z = map->coords[i][j].z;
            map->coords[i][j].x = xy.x * cos(angle) + xy.z * sin(angle);
            map->coords[i][j].z = -xy.x * sin(angle) + xy.z * cos(angle);
        }
    }
}

void rotate_z(t_map *map, double angle)
{
    int i;
    int j;
    t_coord xy;

    i = -1;
    while (++i < map->size.y)
    {
        j = -1;
        while (++j < map->size.x)
        {
            xy.x = map->coords[i][j].x;
            xy.y = map->coords[i][j].y;
            map->coords[i][j].x = xy.x * cos(angle) - xy.y * sin(angle);
            map->coords[i][j].y = xy.x * sin(angle) + xy.y * cos(angle);
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
//    else if (key == 0)
//        rotate_xx(map);
//    else if (key == 13)
//    else if (key == 13)
//    else if (key == 13)
    ft_bzero(map->image, 4 * WIN_X * WIN_Y);
//    ft_printf("hello1\n");
    draw_map(map);
//    ft_printf("hello2\n");
}

void rotatexyz(t_map *map, int key)
{
    move_map_to_centre(map, 1, -WIN_X / 2, -WIN_Y / 2);
    if (key == 0)
        rotate_z(map, 0.1);
    move_map_to_centre(map, 1, WIN_X / 2, WIN_Y / 2);
    ft_bzero(map->image, 4 * WIN_X * WIN_Y);
    draw_map(map);
}

int bonuses(int key, void *map)
{
    if (key == 53)
        exit(1);
    else if (key >= 123 && key <= 126)
    {
        movexy(map, key);
    }
    else if (key == 0)
    {
        rotatexyz(map, key);
    }
    return (1);
}

