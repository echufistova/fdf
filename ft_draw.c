/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:08:57 by ychufist          #+#    #+#             */
/*   Updated: 2019/03/20 17:33:59 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		exit_x(int keycode)
{
	keycode = 0;
	exit(0);
}

void	color(t_map *map, t_point xy, t_coord c0)
{
	if (xy.x >= 0 && xy.x < WIN_X && xy.y >= 0 && xy.y < WIN_Y)
		map->image[xy.x + (xy.y * WIN_X)] = (c0.color != 0) ? c0.color :
			0x8fcbc;
}

void	draw_line(t_map *map, t_coord c0, t_coord c1)
{
	t_point	xy;

	xy.x = c0.x;
	xy.y = c0.y;
	if (fabs(c1.y - c0.y) > fabs(c1.x - c0.x))
	{
		while (c0.y > c1.y ? xy.y >= c1.y : xy.y <= c1.y &&
				xy.x + (xy.y * WIN_X) < WIN_X * WIN_Y)
		{
			xy.x = ((xy.y - c0.y) / (c0.y - c1.y) * (c0.x - c1.x) + c0.x);
			color(map, xy, c0);
			c1.y > c0.y ? xy.y++ : xy.y--;
		}
	}
	else
	{
		while (c0.x > c1.x ? xy.x >= c1.x : xy.x <= c1.x &&
				xy.x + (xy.y * WIN_X) < WIN_X * WIN_Y)
		{
			xy.y = ((xy.x - c0.x) / (c0.x - c1.x) * (c0.y - c1.y) + c0.y);
			color(map, xy, c0);
			c1.x > c0.x ? xy.x++ : xy.x--;
		}
	}
}

void	draw_net(t_map *map)
{
	int i;
	int j;

	i = -1;
	while (++i < map->size.y)
	{
		j = -1;
		while (++j < map->size.x - 1)
			draw_line(map, map->coords[i][j], map->coords[i][j + 1]);
	}
	i = -1;
	while (++i < map->size.y - 1)
	{
		j = -1;
		while (++j < map->size.x)
			draw_line(map, map->coords[i][j], map->coords[i + 1][j]);
	}
}

void	draw_map(t_map *map)
{
	draw_net(map);
	mlx_put_image_to_window(map->mlx, map->window, map->img, 0, 0);
	mlx_hook(map->window, 2, 0, bonuses, map);
	mlx_hook(map->window, 17, 1L << 17, exit_x, 0);
}
