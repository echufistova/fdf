/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coords.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:03:09 by ychufist          #+#    #+#             */
/*   Updated: 2019/03/20 16:38:04 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				validation(char *line)
{
	char *dop;

	dop = line;
	if (!ft_strstr(line, ",0x"))
	{
		while (*dop != '\0' && *dop >= 48 && *dop <= 57)
			dop++;
		if (*dop != '\0')
			return (0);
	}
	return (1);
}

int				make_color(char *line, t_list_coord **res, int i)
{
	char	*dop;
	int		j;

	j = 0;
	if (i == 0)
		(*res)->z = ft_atoi(line);
	if (ft_strstr(line, ",0x"))
	{
		dop = ft_strstr(line, ",0x");
		dop += 3;
		(*res)->color = ft_atoi_base(dop, 16);
	}
	if (!validation(line))
		return (0);
	return (1);
}

void			make_coords(t_map *map)
{
	t_point			ij;
	t_list_coord	*dop;

	ij.y = 0;
	dop = map->begin;
	map->coords = (t_coord**)malloc(sizeof(t_coord*) * map->size.y);
	while (ij.y < map->size.y)
	{
		ij.x = 0;
		map->coords[ij.y] = (t_coord*)malloc(sizeof(t_coord) * map->size.x);
		while (ij.x < map->size.x)
		{
			map->coords[ij.y][ij.x].x = dop->x * 20;
			map->coords[ij.y][ij.x].y = dop->y * 20;
			map->coords[ij.y][ij.x].z = dop->z * 5;
			map->coords[ij.y][ij.x].color = dop->color;
			if (dop->flag_eo_line != 1)
				dop = dop->next;
			ij.x++;
		}
		ij.y++;
		dop = dop->next;
	}
}

t_list_coord	*ft_list_coord_new(int x, int y, char *line)
{
	t_list_coord	*res;

	if (!(res = (t_list_coord*)malloc(sizeof(t_list_coord))))
		return (NULL);
	res->x = x;
	res->y = y;
	res->z = ft_getnbr(line);
	res->color = 0;
	if (!make_color(line, &res, 1))
	{
		free(res);
		return (NULL);
	}
	res->flag_eo_line = 0;
	res->next = NULL;
	return (res);
}

void			free_split(char **split, char *line)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	free(line);
}
