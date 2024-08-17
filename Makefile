# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/13 13:34:27 by athonda           #+#    #+#              #
#    Updated: 2024/08/17 19:35:13 by athonda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

SRCS	=	pipex.c get_fullpath.c exec_cmd.c \
			free_split.c ft_split.c utils.c

OBJS	=	$(patsubst %.c,%.o,$(SRCS))

CFLAGS	=	-Wall -Wextra -Werror -g3 -O0

LIBFT_DIR	=	./libft
LIBFT		=	libft.a

all: $(NAME)

$(NAME): $(OBJS)
		cc $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c pipex.h
		cc $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME) $(LIB)

re: fclean all

.PHONY: all clean fclean re