#include <stdio.h>
#include "fdf.h"


void get_line_fdf(t_map *map, char *line, int row)
{
    t_point ij;
    char **split;
    t_list_coord *dop;

    ij.x = -1;
    split = ft_strsplit(line, ' ');
    dop = map->list_coord;
    while (split[++ij.x] != '\0')
    {
        map->list_coord->next = ft_list_coord_new(ij.x, row, split[ij.x]);
        map->list_coord = map->list_coord->next;
    }
    map->list_coord->flag_eo_line = 1;
    print_list_coord(dop);
//    ft_printf("\n\n");
}

void init(t_map *map)
{
    map->list_coord = (t_list_coord*)malloc(sizeof(t_list_coord));
    map->list_coord->next = NULL;
    map->begin = map->list_coord;
}

void make_coords(t_map *map)
{
//    int color;
    t_point ij;
    t_list_coord *dop;

    ij.y = -1;
    dop = map->begin;
    map->coords = (t_coord**)malloc(sizeof(t_coord*) * map->size.y);
    while (++ij.y < map->list_coord->y)
    {
        ij.x = -1;
        map->coords[++ij.x] = (t_coord*)malloc(sizeof(t_coord) * map->size.x);
        while (dop->flag_eo_line != 1)
        {
            map->coords[ij.y][ij.x].x = dop->x;
            map->coords[ij.y][ij.x].y = dop->y;
            map->coords[ij.y][ij.x].z = dop->z;
            map->coords[ij.y][ij.x].color = dop->color;
            dop = dop->next;
            ft_printf("%4d", map->coords[ij.y][ij.x].z);
        }
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
    map.size.x = len;
    map.size.y = row;
//    if (valid_map(map))
//        make_coords(&map);
    printf("Hello, World!\n");
    return 0;
}
