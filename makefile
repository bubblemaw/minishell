# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maw <maw@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 00:38:47 by maw               #+#    #+#              #
#    Updated: 2025/02/12 00:49:58 by maw              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = pseudo_code.c \
		liste_chaine.c \
		search_cmd.c \

OBJS = $(SRCS:%.c=%.o)

FT_PRINTF = FT_PRINTF

FLAGS = -Wall -Wextra -Werror

RM = rm -f






