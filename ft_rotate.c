/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:14:22 by ychufist          #+#    #+#             */
/*   Updated: 2019/03/19 15:27:13 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_map *map, double angle)
{
	int		i;
	int		j;
	t_coord	xy;

	i = -1;
	while (++i < map->size.y)
	{
		j = -1;
		while (++j < map->size.x)
		{
			xy.y = map->coords[i][j].y;
			xy.z = map->coords[i][j].z;
			map->coords[i][j].y = xy.y * cos(angle) + xy.z * sin(angle);
			map->coords[i][j].z = -xy.y * sin(angle) + xy.z * cos(angle);
		}
	}
}

void	rotate_y(t_map *map, double angle)
{
	int		i;
	int		j;
	t_coord	xy;

	i = -1;
	while (++i < map->size.y)
	{
		j = -1;
		while (++j < map->size.x)
		{
			xy.x = map->coords[i][j].x;
			xy.z = map->coords[i][j].z;
			map->coords[i][j].x = xy.x * cos(angle) + xy.z * sin(angle);
			map->coords[i][j].z = -xy.x * sin(angle) + xy.z * cos(angle);
		}
	}
}

void	rotate_z(t_map *map, double angle)
{
	int		i;
	int		j;
	t_coord	xy;

	i = -1;
	while (++i < map->size.y)
	{
		j = -1;
		while (++j < map->size.x)
		{
			xy.x = map->coords[i][j].x;
			xy.y = map->coords[i][j].y;
			map->coords[i][j].x = xy.x * cos(angle) - xy.y * sin(angle);
			map->coords[i][j].y = xy.x * sin(angle) + xy.y * cos(angle);
		}
	}
}

void	rotatexyz(t_map *map, int key)
{
	move_map_to_centre(map, 1, -WIN_X / 2, -WIN_Y / 2);
	if (key == 0)
		rotate_y(map, 0.1);
	else if (key == 2)
		rotate_y(map, -0.1);
	else if (key == 13)
		rotate_x(map, 0.1);
	else if (key == 1)
		rotate_x(map, -0.1);
	else if (key == 6)
		rotate_z(map, 0.1);
	else if (key == 8)
		rotate_z(map, -0.1);
	move_map_to_centre(map, 1, WIN_X / 2, WIN_Y / 2);
	ft_bzero(map->image, 4 * WIN_X * WIN_Y);
	draw_map(map);
}
