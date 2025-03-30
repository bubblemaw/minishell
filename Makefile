# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: david <david@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 22:16:43 by david             #+#    #+#              #
#    Updated: 2025/03/30 20:56:04 by david            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

SRCS =  srcs/main/main.c \
	    srcs/tokken/creat_token.c \
	    srcs/tokken/token_detect.c \
	    srcs/tokken/token_parse.c \
		srcs/tokken/creat_list.c \
		srcs/execution/execution.c \
		srcs/token_to_cmd/utils_cmd_lst.c \
		srcs/cmd_parsing/search_cmd.c \
		srcs/redirection/redirection.c \
		srcs/error_free/error.c \
		srcs/error_free/free.c \
		srcs/token_to_cmd/add_cmd_lst.c \
		srcs/builtin/echo.c \
		srcs/builtin/export.c \
		srcs/builtin/cd.c \
		srcs/builtin/env.c \
		srcs/builtin/pwd.c \
		srcs/builtin/unset.c \
		srcs/builtin/exit.c \
		srcs/expansion/expansion.c \
		srcs/expansion/var_local.c \
		srcs/expansion/creat_var_list.c \
		srcs/expansion/kill_quotes.c \
		srcs/expansion/var_priorities.c \
		srcs/builtin/built_in.c \
		srcs/main/init_minishell.c \
		srcs/token_to_cmd/token_to_cmd.c \
		srcs/token_to_cmd/redirection_token_to_cmd.c \
		srcs/token_to_cmd/save_redirection.c \
		srcs/utils/utils1.c \
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
