/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychufist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:50:36 by ychufist          #+#    #+#             */
/*   Updated: 2019/03/20 16:33:51 by ychufist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_FDF_H
# define FDF_FDF_H
# define WIN_X 1200
# define WIN_Y 800

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "libft/ft_printf.h"
# include "mlx.h"
# include "math.h"

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_coord
{
	double				x;
	double				y;
	double				z;
	int					color;
}						t_coord;

typedef struct			s_list_coord
{
	double				x;
	double				y;
	double				z;
	int					color;
	int					flag_eo_line;
	struct s_list_coord	*next;
}						t_list_coord;

typedef struct			s_map
{
	t_point				size;
	t_list_coord		*list_coord;
	t_list_coord		*begin;
	t_coord				**coords;
	void				*mlx;
	void				*window;
	void				*img;
	int					*image;
	int					endian;
	int					bpp;
	int					size_line;
	int					iso;
}						t_map;

void					usage(int i);
void					draw_net(t_map *map);
void					draw_map(t_map *map);
void					draw_line(t_map *map, t_coord c0, t_coord c1);
void					make_coords(t_map *map);
int						make_color(char *line, t_list_coord **res, int i);
void					move_map_to_centre(t_map *map, int n, int p1, int p2);
void					rotate_x(t_map *map, double angle);
void					rotate_y(t_map *map, double angle);
void					rotate_z(t_map *map, double angle);
void					rotatexyz(t_map *map, int key);
void					recount_map_xyz(t_map *map, int key, int num);
int						bonuses(int key, void *map);
void					free_split(char **split, char *line);
t_list_coord			*ft_list_coord_new(int x, int y, char *line);

#endif
