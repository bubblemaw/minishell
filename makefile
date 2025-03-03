# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maw <maw@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 00:38:47 by maw               #+#    #+#              #
#    Updated: 2025/03/03 19:22:14 by maw              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = srcs/pseudo_code.c \
		srcs/liste_chaine.c \
		srcs/liste_chaine_double.c \
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
		GNL/get_next_line_utils.c \
		
OBJS = $(SRCS:%.c=%.o)

FT_PRINTF = FT_PRINTF/

FLAGS = -Wall -Wextra -Werror

RM = rm -f

$(NAME):$(OBJS)
		$(MAKE) -C $(FT_PRINTF)
		gcc $(FLAGS) $(OBJS) $(FT_PRINTF)libftprintf.a -o $(NAME)

all:$(NAME)

clean :
	$(RM) $(OBJS)
	$(MAKE) -C $(FT_PRINTF) clean

fclean: clean
		$(RM) $(NAME)
		$(RM) $(FT_PRINTF)libftprintf.a
		$(RM) $(FT_PRINTF)LIBFT/libft.a

re: fclean all

