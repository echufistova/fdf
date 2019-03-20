/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:31:29 by ychufist          #+#    #+#             */
/*   Updated: 2019/03/19 15:42:56 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void free_split(char **split, char *line)
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

int		same_amount_of_coords(t_map *map, char **split, int row)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	if (row == 0)
		map->size.x = i;
	else if (i != map->size.x)
		return (0);
	return (1);
}

int		get_map_list(t_map *map, int fd)
{
	int		i;
	char	*line;
	char	**split;
	int		row;

	row = -1;
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		i = (++row == 0) ? 0 : -1;
		if (!same_amount_of_coords(map, split, row)|| (i == 0 && row == 0 &&
			!make_color(split[i], &map->list_coord, 0)))
		{
			ft_printf("tut blin\n");
			free_split(split, line);
			return (0);
		}
		while (split[++i])
		{
			if ((map->list_coord->next = ft_list_coord_new(i, row, split[i]))
				== NULL)
			{
				ft_printf("tut\n");
				free_split(split, line);
				return (0);
			}
			map->list_coord = map->list_coord->next;
		}
		map->list_coord->flag_eo_line = 1;
		// while (--i >= 0)
		// 	free(split[i]);
		// free(split);
		ft_printf("tut blin\n");
		free_split(split, line);
	}
	map->size.y = row + 1;
	return (1);
}

void	recount_map_xyz(t_map *map, int key, int num)
{
	t_point	ij;

	ij.y = -1;
	while (++ij.y < map->size.y)
	{
		ij.x = -1;
		while (++ij.x < map->size.x)
		{
			if (key == 123 || key == 124)
				map->coords[ij.y][ij.x].x += num;
			else if (key == 125 || key == 126)
				map->coords[ij.y][ij.x].y += num;
		}
	}
}

void	init(t_map *map)
{
	map->list_coord = (t_list_coord*)malloc(sizeof(t_list_coord));
	map->list_coord->next = NULL;
	map->list_coord->x = 0;
	map->list_coord->y = 0;
	map->list_coord->color = 0;
	map->begin = map->list_coord;
	map->coords = NULL;
	map->mlx = mlx_init();
	map->window = mlx_new_window(map->mlx, WIN_X, WIN_Y, "FDF");
	map->endian = 0;
	map->bpp = 32;
	map->img = mlx_new_image(map->mlx, WIN_X, WIN_Y);
	map->image = (int *)mlx_get_data_addr(map->img, &map->bpp,
			&map->size_line, &map->endian);
}

int		main(int ac, char **av)
{
	int		fd;
	t_map	map;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
	{
		usage();
		return (0);
	}
	init(&map);
	ft_printf("kek\n");
	if (!get_map_list(&map, fd))
	{
		   system("leaks fdf");
		ft_printf("error\n");
		return (0);
	}
	ft_printf("ke111k\n");
	//    if (valid_map(map))
	make_coords(&map);
	ft_printf("here\n");
	move_map_to_centre(&map, 0, 0, 0);
	ft_printf("here2\n");
	rotate_x(&map, 0);
	rotate_y(&map, 0);
	rotate_z(&map, 0);
	ft_printf("here3\n");
	move_map_to_centre(&map, 1, WIN_X / 2, WIN_Y / 2);
	ft_printf("here4\n");
	draw_map(&map);
	ft_printf("here5\n");
	mlx_loop(map.mlx);
//    system("leaks fdf");
	return (0);
}
