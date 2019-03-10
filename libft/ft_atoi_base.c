//
// Created by echufy on 10.03.19.
//

#include "libft.h"

static int		ft_isspace(char c)
{
    if (c == '\n' || c == '\v' || c == '\t' ||
        c == ' ' || c == '\r' || c == '\f')
        return (1);
    return (0);
}

static int	ft_base_atoi(char c, char *base)
{
    int		i;

    i = 0;
    while (base[i])
    {
        if (base[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

int			ft_atoi_base(char *str, char *base)
{
    int		res;
    int		sign;
    int		i;

    res = 0;
    sign = 1;
    i = 0;
    while ((ft_isspace(str[i]) != '\0'))
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (ft_base_atoi(str[i], base) != -1)
    {
        res = res * ft_strlen(base) + ft_base_atoi(str[i], base);
        i++;
    }
    return (res * sign);
}