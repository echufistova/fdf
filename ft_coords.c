//
// Created by Yevheniya CHUFISTOVA on 2019-03-14.
//

#include "fdf.h"

void make_coords(t_map *map)
{
//    int color;
    int i;
    t_point ij;
    t_point xy;
    t_list_coord *dop;

    ij.y = 0;
//    ft_printf("nap size y : %d ", map->size.y);
//    ft_printf("nap size x : %d\n", map->size.x);
    dop = map->begin;
    map->coords = (t_coord**)malloc(sizeof(t_coord*) * map->size.y);
    while (ij.y < map->size.y)
    {
        ij.x = 0;
        map->coords[ij.y] = (t_coord*)malloc(sizeof(t_coord) * map->size.x);
        while (ij.x < map->size.x)
        {
//            printf("dop->x: %f\n", dop->x);
            map->coords[ij.y][ij.x].x = dop->x * 20;
            map->coords[ij.y][ij.x].y = dop->y * 20;
            map->coords[ij.y][ij.x].z = dop->z * 5;
            map->coords[ij.y][ij.x].color = dop->color;
            if (dop->flag_eo_line != 1)
                dop = dop->next;
//            printf("t%10f", map->coords[ij.y][ij.x].z);
            ij.x++;
        }
        ij.y++;
        dop = dop->next;
        ft_printf("   h\n");
    }
    dop = map->begin;
//    free_list(&dop);
}