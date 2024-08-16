# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/13 13:34:27 by athonda           #+#    #+#              #
#    Updated: 2024/08/16 13:04:41 by athonda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

LIB		=	libpipx.a

MAIN	=	pipex.c

SRCS	=	pipex.c get_fullpath.c exec_cmd.c \
			free_split.c ft_split.c utils.c

OBJS	=	$(patsubst %.c,%.o,$(SRCS))

CFLAGS	=	-Wall -Wextra -Werror -g3 -O0

all: $(MAIN) $(LIB)
		cc $(CFLAGS) $(MAIN) $(LIB) -o $(NAME)

$(LIB): $(OBJS)
		ar rsc $@ $?

%.o: %.c pipex.h
		cc $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME) $(LIB)

re: fclean all

.PHONY: all clean fclean re