//
// Created by Yevheniya CHUFISTOVA on 2019-03-19.
//

#include "libft.h"

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