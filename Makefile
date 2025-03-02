# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 22:16:43 by david             #+#    #+#              #
#    Updated: 2025/02/25 16:31:55 by dchellen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

SRCS = main.c \
	   creat_token.c \
	   token_detect.c \
	   token_parse.c \
	   creat_list.c

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
