# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/13 13:34:27 by athonda           #+#    #+#              #
#    Updated: 2024/08/17 22:05:12 by athonda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

SRCS	=	pipex.c get_fullpath.c exec_cmd.c \
			free_split.c

OBJS	=	$(patsubst %.c,%.o,$(SRCS))

CFLAGS	=	-Wall -Wextra -Werror -g3 -O0

LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		cc $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR)

%.o: %.c pipex.h
		cc $(CFLAGS) -c $< -o $@

clean:
		$(MAKE) clean -C $(LIBFT_DIR)
		rm -f $(OBJS)

fclean: clean
		$(MAKE) fclean -C $(LIBFT_DIR)
		rm -f $(NAME) $(LIB)

re: fclean all

.PHONY: all clean fclean re