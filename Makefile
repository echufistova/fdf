# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychufist <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 16:59:50 by ychufist          #+#    #+#              #
#    Updated: 2019/03/11 17:05:33 by ychufist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIBFT = ./libft/libftprintf.a

FLAGS =

SRC = main.c ft_list_coord.c ft_coords.c ft_draw.c ft_moves.c

OUT = $(SRC:.c=.o)

HDR = fdf.h

all: lib $(NAME)

lib:
	make -C ./libft

$(NAME): $(OUT) $(LIBFT)
	gcc -o $(NAME) $(FLAGS) -lmlx -framework OpenGL -framework AppKit $(LIBFT) $(SRC)

%.o: %.c $(HDR)
	gcc $(FLAGS) -o $@ -c $< -I ./libft

clean:
	make clean -C ./libft
	/bin/rm -f $(OUT)
	/bin/rm -f *~

fclean: clean
	make fclean -C ./libft
	/bin/rm -f $(NAME)	

re: fclean all
