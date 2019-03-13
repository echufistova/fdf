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
            printf("hh %d : ", i);
            map->list_coord->next = ft_list_coord_new(i, row, split[i]);
            map->list_coord = map->list_coord->next;
            printf("%3f", map->list_coord->z);
        }
        ft_printf("dd %d ", i);
        printf("\n");
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
    t_point xy;
    t_list_coord *dop;

    ij.y = 0;
    xy.x = map->size.x / 2;//(map->win_x - map->size.x * 20) / 2;
    xy.y = map->size.y / 2;//(map->win_y - map->size.y * 20) / 2;
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
            map->coords[ij.y][ij.x].x = (dop->x + xy.x) * 20;
            map->coords[ij.y][ij.x].y = (dop->y + xy.y) * 20;
            map->coords[ij.y][ij.x].z = dop->z * 10;
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
    dop = map->begin;
//    free_list(&dop);
}

void make_window(t_map *map)
{
    map->mlx = mlx_init();
    map->win_x = 1000;
    map->win_y = 700;
    map->window = mlx_new_window(map->mlx, map->win_x,
                                 map->win_y, "FDF");
    map->endian = 0;
    map->bpp = 32;
    map->img = mlx_new_image(map->mlx, map->win_x, map->win_y);
    map->image = (int *) mlx_get_data_addr(map->img, &map->bpp,
            &map->size_line, &map->endian);
}

void draw_line(t_map *map, t_coord c0, t_coord c1)
{
//    printf("here4\n");
     t_point xy;

    xy.x = c0.x;
    printf("x: %d ", xy.x);
    xy.y = c0.y;
    printf("y: %d \n", xy.y);
    if (fabs(c1.y - c0.y) > fabs(c1.x - c0.x)) {
        while (c0.y > c1.y ? xy.y >= c1.y : xy.y <= c1.y) //вставляем по х
        {
            xy.x = ((xy.y - c0.y) / (c0.y - c1.y) * (c0.x - c1.x) + c0.x);
            map->image[xy.x + (xy.y * map->win_x)] = 0x8fcbc;
            c1.y > c0.y ? xy.y++ : xy.y--;
        }
        printf("here5\n");
    }
    else
        {
        while (c0.x > c1.x ? xy.x >= c1.x : xy.x <= c1.x) //вставляем по у
        {
            xy.y = ((xy.x - c0.x) / (c0.x - c1.x) * (c0.y - c1.y) + c0.y);
            map->image[xy.x + (xy.y * map->win_x)] = 0x8fcbc;
            c1.x > c0.x ? xy.x++ : xy.x--;
        }
        printf("here6\n");
    }
}

void draw(t_map *map)
{
    t_point	xy;

    xy.y = -1;
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
    draw(map);
    ft_printf("here3\n");
    mlx_put_image_to_window(map->mlx, map->window, map->img, 0, 0);
    system("leaks fdf");
    mlx_loop(map->mlx);
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
    ft_printf("here\n");
    make_window(&map);
    ft_printf("here1\n");
    draw_map(&map);
//    ft_printf("here2\n");
    printf("Hello, World!\n");
    system("leaks fdf");
    return (0);
}
