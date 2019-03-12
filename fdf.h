//
// Created by Yevheniya CHUFISTOVA on 2019-03-07.
//

#ifndef FDF_FDF_H
#define FDF_FDF_H

#include "libft/libft.h"
#include "libft/get_next_line.h"
#include "libft/ft_printf.h"
# include "minilibx/mlx.h"
#include "math.h"

typedef struct s_point
{
    int x;
    int y;
}               t_point;

typedef struct s_coord
{
    double x;
    double y;
    double z;
    double color;

}               t_coord;

typedef struct s_list_coord
{
    double x;
    double y;
    double z;
    int color;
    int flag_eo_line;
    struct s_list_coord *next;

}               t_list_coord;

typedef struct s_map
{
    t_point             size;
    t_list_coord        *list_coord;
    t_list_coord        *begin;
    t_coord             **coords;
    void                *mlx;
    void                *window;
    void *img;
    int *image;
    int endian;
    int bpp;
    int size_line;
    int win_x;
    int win_y;
}               t_map;

void print_list_coord(t_list_coord *list);
t_list_coord	*ft_list_coord_new(int x, int y, char *line);
#endif //FDF_FDF_H
