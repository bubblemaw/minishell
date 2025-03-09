# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: david <david@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 22:16:43 by david             #+#    #+#              #
#    Updated: 2025/03/07 17:47:49 by david            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

SRCS = main.c \
	   creat_token.c \
	   token_detect.c \
	   token_parse.c \
	   creat_list.c \
		srcs/pseudo_code.c \
		srcs/liste_chaine.c \
		srcs/search_cmd.c \
		srcs/redirection.c \
		srcs/error.c \
		srcs/cmd_lst.c \
		srcs/echo.c \
		srcs/expansion.c \
		srcs/built_in.c \
		srcs/init_minishell.c \
		srcs/token_cmd.c \
		srcs/utils1.c \
		GNL/get_next_line.c \

FLAGS = -Wall -Wextra -Werror  -g

LIBS = -lreadline

RM = rm -f

OBJS = $(SRCS:%.c=%.o)

LIBFT_PATH = libft/

LIBFT_LIB = $(LIBFT_PATH)libft.a

$(NAME): subsystems $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT_LIB) $(LIBS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

subsystems:
	@make -C $(LIBFT_PATH) all

all: $(NAME)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all
