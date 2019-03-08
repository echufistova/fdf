//
// Created by Yevheniya CHUFISTOVA on 2019-03-07.
//

#ifndef FDF_FDF_H
#define FDF_FDF_H

#include "libft/libft.h"
#include "libft/get_next_line.h"
#include "libft/ft_printf.h"

typedef struct s_point
{
    int x;
    int y;
}               t_point;

typedef struct s_coord
{
    int x;
    int y;
    int z;
    int color;

}               t_coord;

typedef struct s_list_coord
{
    int x;
    int y;
    int z;
    int color;
    struct s_list_coord *next;
    struct s_list_coord *prev;

}               t_list_coord;

typedef struct s_map
{
    t_point     map_size;
    t_list_coord      *list_coord;
    t_coord     *coords;
}               t_map;
#endif //FDF_FDF_H
