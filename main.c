#include <stdio.h>
#include "fdf.h"


void get_line_fdf(t_map *map, char *line, int row)
{
    int i;
    char **split;

    split = ft_strsplit(line, ' ');
    i = (row == 0) ? 1 : 0;
    while (split[i])
    {
        map->list_coord->next = ft_list_coord_new(i, row, split[i]);
        map->list_coord = map->list_coord->next;
        ft_printf("%3d", map->list_coord->z);
        i++;
    }
    ft_printf(" %d", i);
    ft_printf("\n");
//    map->list_coord->z = ft_atoi(split[0]); // ТУТ ЕЩЕ НУЖНО ДОБАВИТЬ ЦВЕТ
    map->list_coord->flag_eo_line = 1;
}

void init(t_map *map)
{
    map->list_coord = (t_list_coord*)malloc(sizeof(t_list_coord));
    map->list_coord->next = NULL;
    map->list_coord->x = 0;
    map->list_coord->y = 0;
    map->list_coord->z = 0; //ТУТ НЕ 0
    map->begin = map->list_coord;
}

void make_coords(t_map *map)
{
//    int color;
    t_point ij;
    t_list_coord *dop;

    ij.y = 0;
    ft_printf("nap size y : %d ", map->size.y);
    ft_printf("nap size x : %d\n", map->size.x);
    dop = map->begin;
    map->coords = (t_coord**)malloc(sizeof(t_coord*) * map->size.y);
    while (ij.y < map->size.y)
    {
        ij.x = 0;
        map->coords[ij.y] = (t_coord*)malloc(sizeof(t_coord) * map->size.x);
        while (ij.x < map->size.x)
        {
            map->coords[ij.y][ij.x].x = dop->x;
            map->coords[ij.y][ij.x].y = dop->y;
            map->coords[ij.y][ij.x].z = dop->z;
            map->coords[ij.y][ij.x].color = dop->color;
            if (dop->flag_eo_line != 1)
                dop = dop->next;
            ft_printf("%3d", map->coords[ij.y][ij.x].z);
            ij.x++;
        }
        ij.y++;
        dop = dop->next;
        ft_printf("   h\n");
    }
}

int main(int ac, char **av)
{
    int fd;
    int row;
    int len;
    char *line;
    t_map map;

    row = 0;
    fd = open(av[1], O_RDONLY);
    init(&map);
    while (get_next_line(fd, &line) > 0)
    {
        if (row == 0)
            len = ft_strlen(line);
        if (ft_strlen(line) > len)
        {
            ft_strdel(&line);
            return (0);
        }
        get_line_fdf(&map, line, row++);
        ft_strdel(&line);
    }
    ft_printf("\n");
    map.size.x = map.list_coord->x + 1;
    map.size.y = row;
//    if (valid_map(map))
        make_coords(&map);
    printf("Hello, World!\n");
    return 0;
}
