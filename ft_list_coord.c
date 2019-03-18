//
// Created by Yevheniya CHUFISTOVA on 2019-03-08.
//

#include "fdf.h"

int	ft_getnbr(char *str)
{
    size_t	i;
    int		result;

    result = 0;
    i = 0;
    while (str[i] != '\0' && str[i] == ' ')
        i++;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while ((str[i] >= '0') && (str[i] <= '9'))
    {
        result = (result * 10) + (str[i] - '0');
        i++;
    }
    if (str[0] == '-')
        result = result * (-1);
    return (result);
}

t_list_coord	*ft_list_coord_new(int x, int y, char *line)
{
    char *dop;
    t_list_coord *res;

    if (!(res = (t_list_coord*)malloc(sizeof(t_list_coord))))
        return (NULL);
    res->x = x;
    res->y = y;
    res->z = ft_atoi(line);
    ft_printf("'%s'\n", line);
    printf("here z %f\n", res->z);
    if (ft_strchr(line, ','))
    {
        dop = ft_strchr(line, ',');
        ft_printf("dop: '%s'\n", dop);
        ft_printf("%d\n", ft_atoi_base(++dop, 16));
        res->color = ft_atoi_base(dop, 16);
        ft_printf("color : %d\n\n", res->color);
        res->color = 5;
    }
    else
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