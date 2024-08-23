# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/13 13:34:27 by athonda           #+#    #+#              #
#    Updated: 2024/08/23 22:05:52 by athonda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

SRCS	=	pipex.c get_fullpath.c exec_cmd.c free_split.c \
			error.c wait_all.c

OBJS	=	$(patsubst %.c,%.o,$(SRCS))

CFLAGS	=	-Wall -Wextra -Werror

LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

NAME_BONUS	=	pipex_bonus

SRCS_BONUS	=	pipex_bonus.c get_fullpath.c exec_cmd.c free_split.c \
				error.c wait_all.c

OBJS_BONUS	=	$(patsubst %.c,%.o,$(SRCS_BONUS))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		cc $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR)

%.o: %.c pipex.h
		cc $(CFLAGS) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
		cc $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)

clean:
		$(MAKE) clean -C $(LIBFT_DIR)
		rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
		$(MAKE) fclean -C $(LIBFT_DIR)
		rm -f $(NAME) $(LIB) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re