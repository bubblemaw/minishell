# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 22:16:43 by david             #+#    #+#              #
#    Updated: 2025/04/23 09:02:58 by dchellen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

SRCS =  srcs/main/main.c \
	    srcs/tokken/creat_token.c \
	    srcs/tokken/token_detect.c \
	    srcs/tokken/token_detect_2.c \
	    srcs/tokken/token_parse.c \
		srcs/tokken/creat_list.c \
		srcs/tokken/var_error.c \
		srcs/execution/execution.c \
		srcs/execution/pipe.c \
		srcs/execution/pipe_utils.c \
		srcs/token_to_cmd/utils_cmd_lst.c \
		srcs/cmd_parsing/search_cmd.c \
		srcs/redirection/redirection.c \
		srcs/redirection/redirection_fake.c \
		srcs/redirection/here_doc.c \
		srcs/redirection/here_doc_utils.c \
		srcs/error_free/error.c \
		srcs/error_free/free.c \
		srcs/token_to_cmd/add_cmd_lst.c \
		srcs/builtin/echo.c \
		srcs/builtin/export.c \
		srcs/builtin/make_export.c \
		srcs/builtin/export.utils.c \
		srcs/builtin/cd.c \
		srcs/builtin/cd_utils.c \
		srcs/builtin/env.c \
		srcs/builtin/pwd.c \
		srcs/builtin/unset.c \
		srcs/builtin/exit.c \
		srcs/builtin/bubble_sort.c \
		srcs/builtin/bubble_sort_utils.c \
		srcs/expansion/expansion.c \
		srcs/expansion/expansion_spe.c \
		srcs/expansion/expansion_here_doc.c \
		srcs/expansion/switch.c \
		srcs/expansion/switch_utils.c \
		srcs/expansion/var_local.c \
		srcs/expansion/creat_var_list.c \
		srcs/expansion/kill_quotes.c \
		srcs/expansion/kill_quotes_utils.c \
		srcs/expansion/lvl.c \
		srcs/builtin/built_in.c \
		srcs/main/init_minishell.c \
		srcs/token_to_cmd/token_to_cmd.c \
		srcs/token_to_cmd/redirection_token_to_cmd.c \
		srcs/token_to_cmd/save_redirection.c \
		srcs/utils/utils1.c \
		srcs/utils/signal.c \
		GNL/get_next_line.c \

FLAGS = -Wall -Wextra -Werror

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
