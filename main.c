#include <stdio.h>
#include "fdf.h"

int same_amount_of_coords(t_map *map, char **split, int row)
{
    int i;

    i = 0;
    while (split[i])
        i++;
    if (row == 0)
        map->size.x = i;
    else if (i != map->size.x)
        return (0);
    return (1);
}

int get_map_list(t_map *map, int fd)
{
    int i;
    char *line;
    char **split;
    int row;

    row = -1;
    while (get_next_line(fd, &line) > 0)
    {
        split = ft_strsplit(line, ' ');
        i = (++row == 0) ? 0 : -1;
        if (!same_amount_of_coords(map, split, row))
            return (0);
        while (split[++i])
        {
//            ft_printf("hh %d : \n", i);
//            ft_printf(" split: %s\n", split[i]);
            map->list_coord->next = ft_list_coord_new(i, row, split[i]);
            map->list_coord = map->list_coord->next;
//            printf(" map->list_coord->z %3f\n\n", map->list_coord->z);
        }
        printf("\n\n");
//    map->list_coord->z = ft_atoi(split[0]); // ТУТ ЕЩЕ НУЖНО ДОБАВИТЬ ЦВЕТ
        map->list_coord->flag_eo_line = 1;
        while (--i >= 0)
            free(split[i]);
        free(split);
        ft_strdel(&line);
    }
    map->size.y = row + 1;
    return (1);
}

void recount_map_xyz(t_map *map, int key, int num)
{
    t_point ij;

    ij.y = -1;
    while (++ij.y < map->size.y)
    {
        ij.x = -1;
        while (++ij.x < map->size.x)
        {
            if (key == 125 || key == 126)
                map->coords[ij.y][ij.x].y += num;
            else if (key == 123 || key == 124)
                map->coords[ij.y][ij.x].x += num;
        }
    }
}

void xyz_in_xy(t_map *map, double angle)
{
    t_point ij;
    t_coord xy0;
    t_coord xy1;

    ij.y = -1;
    while (++ij.y < map->size.y)
    {
        ij.x = -1;
        while (++ij.x < map->size.x)
        {
            xy0.x = map->coords[ij.y][ij.x].x;
            xy0.y = map->coords[ij.y][ij.x].y * cos(angle) + map->coords[ij.y][ij.x].z * sin(angle);
            xy0.z = map->coords[ij.y][ij.x].z * cos(angle) - map->coords[ij.y][ij.x].y * sin(angle);
            xy1.x = xy0.x * cos(angle) - xy0.z * sin(angle);
            xy1.y = xy0.y;
            xy1.z = xy0.z * cos(angle) + xy0.x * sin(angle);
            map->coords[ij.y][ij.x].x = xy1.x * cos(angle) + xy1.y * sin(angle);
            map->coords[ij.y][ij.x].y = xy1.y * cos(angle) - xy1.x * sin(angle);
        }
    }
}

void make_window(t_map *map)
{
    map->mlx = mlx_init();
    map->win_x = 1200;
    map->win_y = 800;
    map->window = mlx_new_window(map->mlx, map->win_x, map->win_y, "FDF");
    map->endian = 0;
    map->bpp = 32;
    map->img = mlx_new_image(map->mlx, map->win_x, map->win_y);
    map->image = (int *) mlx_get_data_addr(map->img, &map->bpp,
                                           &map->size_line, &map->endian);
}

void init(t_map *map)
{
    map->list_coord = (t_list_coord*)malloc(sizeof(t_list_coord));
    map->list_coord->next = NULL;
    map->list_coord->x = 0;
    map->list_coord->y = 0;
    map->list_coord->z = 0; //ТУТ НЕ 0
    map->begin = map->list_coord;
    map->coords = NULL;
}

int main(int ac, char **av)
{
    int fd;
    t_map map;

    if ((fd = open(av[1], O_RDONLY)) < 0)
        return (0);
    init(&map);
    if (!get_map_list(&map, fd))
        return (0);
    //    if (valid_map(map))
    make_coords(&map);
//    ft_printf("here\n");
    make_window(&map);
//    ft_printf("here1\n");
    xyz_in_xy(&map, 15);
//    ft_printf("hello5\n");
    move_map_to_centre(&map);
    draw_map(&map);
//    ft_printf("here2\n");
//    printf("Hello, World!\n");
    mlx_loop(map.mlx);
//    system("leaks fdf");
    return (0);
}
