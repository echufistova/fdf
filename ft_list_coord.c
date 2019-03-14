//
// Created by Yevheniya CHUFISTOVA on 2019-03-08.
//

#include "fdf.h"

t_list_coord	*ft_list_coord_new(int x, int y, char *line)
{
    // char *dop;
    t_list_coord *res;

    if (!(res = (t_list_coord*)malloc(sizeof(t_list_coord))))
        return (NULL);
    res->x = x;
    res->y = y;
    res->z = ft_atoi(line);
    ft_printf("%s\n", line);
    ft_printf(" %d", res->z);
//    if (ft_strchr(line, ','))
//    {
//        dop = ft_strchr(line, ',');
//        res->color = ft_atoi_base(++dop, "10");
//    }
    //else
    res->color = 0;
    res->flag_eo_line = 0;
    res->next = NULL;
    return (res);
}

void print_list_coord(t_list_coord *list)
{
    t_list_coord *dop;

    dop = list;
    while (dop)
    {
        ft_printf("%4d", dop->z);
        dop = dop->next;
    }
    ft_printf("\n");
}

void			free_list(t_list_coord **dop)
{
    t_list_coord *tmp;

    while (*dop)
    {
        tmp = (*dop)->next;
//        free((*dop)->links);
        free(*dop);
        *dop = tmp;
    }
}