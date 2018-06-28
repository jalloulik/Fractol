# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kjalloul <kjalloul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 17:18:00 by kjalloul          #+#    #+#              #
#    Updated: 2018/01/15 18:14:23 by kjalloul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRCPATH = ./

OBJPATH = ./

IPATHLIB = libft/includes

IPATHGRAPH = libgraph/includes

IPATH = ./

HEADER = fractol.h

SRC = main.c\
		ft_keyhooks.c\
		fractals.c\
		ft_mouse_hooks.c\
		ft_keyhook2.c\
		ft_tools.c

OBJ = $(SRC:%.c=$(OBJPATH)%.o)

SRCF = $(SRCPATH)$(SRC)

FLAG = -Wall -Werror -Wextra

all : $(NAME)

LIB:
	make -C libft/

LIBCLEAN:
	make clean -C libft/
	make clean -C libgraph/
	make clean -C minilibx_macos/

LIBFCLEAN:
	make fclean -C libft/
	make fclean -C libgraph/
	make fclean -C minilibx_macos/

$(OBJ): $(OBJPATH)%.o: $(SRCPATH)%.c $(IPATH)$(HEADER)
	gcc $(FLAG) -o $@ -c $< -I$(IPATH) -I$(IPATHLIB) -I$(IPATHGRAPH) -I minilibx_macos/

$(NAME): $(OBJ)
	make -C libft
	make -C libgraph
	make -C minilibx_macos
	gcc $(FLAG) -o $(NAME) $(OBJ) -Llibft/ -lft -Llibgraph -lgraph -Lminilibx_macos/ -lmlx -framework OpenGL -framework AppKit

clean: LIBCLEAN
	/bin/rm -f $(OBJ)

fclean: clean LIBFCLEAN
	/bin/rm -f $(NAME)

re: fclean all
