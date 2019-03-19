/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:13:57 by ychufist          #+#    #+#             */
/*   Updated: 2019/03/19 15:21:25 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_map_to_centre(t_map *map, int n, int p1, int p2)
{
	t_point	ij;
	t_coord	coord;

	ij.y = -1;
	while (++ij.y < map->size.y)
	{
		ij.x = -1;
		while (++ij.x < map->size.x)
		{
			coord.x = map->coords[ij.y][ij.x].x;
			coord.y = map->coords[ij.y][ij.x].y;
			if (n == 0)
			{
				map->coords[ij.y][ij.x].x = coord.x - map->size.x * 10;
				map->coords[ij.y][ij.x].y = coord.y - map->size.y * 10;
			}
			if (n == 1)
			{
				map->coords[ij.y][ij.x].x = coord.x + p1;
				map->coords[ij.y][ij.x].y = coord.y + p2;
			}
		}
	}
}

void	movexy(t_map *map, int key)
{
	if (key == 123)
		recount_map_xyz(map, 123, -10);
	else if (key == 124)
		recount_map_xyz(map, 124, 10);
	else if (key == 125)
		recount_map_xyz(map, 125, 10);
	else if (key == 126)
		recount_map_xyz(map, 126, -10);
	ft_bzero(map->image, 4 * WIN_X * WIN_Y);
	draw_map(map);
}

void	zoom(t_map *map, int key)
{
	int		i;
	int		j;
	double	k;

	i = -1;
	k = (key == 24) ? 1.1 : 0.9;
	move_map_to_centre(map, 1, -WIN_X / 2, -WIN_Y / 2);
	while (++i < map->size.y)
	{
		j = -1;
		while (++j < map->size.x)
		{
			map->coords[i][j].x *= k;
			map->coords[i][j].y *= k;
			map->coords[i][j].z *= k;
		}
	}
	move_map_to_centre(map, 1, WIN_X / 2, WIN_Y / 2);
	ft_bzero(map->image, 4 * WIN_X * WIN_Y);
	draw_map(map);
}

int		bonuses(int key, void *map)
{
	if (key == 53)
	{
		system("leaks fdf");
		exit(1);
	}
	else if (key >= 123 && key <= 126)
		movexy(map, key);
	else if ((key >= 0 && key <= 2) || key == 13 || key == 8 || key == 6)
		rotatexyz(map, key);
	else if (key == 24 || key == 27)
		zoom(map, key);
	return (1);
}

void	guide(t_map *map)
{
	mlx_string_put(map->mlx, map->window, 10, 25, 0xf5978a, "rotate");
}

void	usage(void)
{
	ft_printf("Usage: ./fdf <map_name>\n");
}
