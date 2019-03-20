/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coords.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:03:09 by ychufist          #+#    #+#             */
/*   Updated: 2019/03/19 15:08:15 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			make_color(char *line, t_list_coord **res, int i)
{
	char *dop;

	if (i == 0)
		(*res)->z = ft_atoi(line);
	// ft_printf("hello z\n");
	if (ft_strstr(line, ",0x"))
	{
		ft_printf("lol\n");
		dop = ft_strstr(line, ",0x");
		dop += 2;
		ft_printf("%s\n", dop);
		(*res)->color = ft_atoi_base(++dop, 16);
	}
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
			ft_printf("%f  ", map->coords[ij.y][ij.x].z);
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
	make_color(line, &res, 1);
	res->flag_eo_line = 0;
	res->next = NULL;
	return (res);
}

void			print_list_coord(t_list_coord *list)
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
