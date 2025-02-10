# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: david <david@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 22:16:43 by david             #+#    #+#              #
#    Updated: 2025/02/10 22:37:44 by david            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

SRCS = test_tokken.c

FLAGS = -Wall -Wextra -Werror

LIBS = -lreadline

RM = rm -f

OBJS = $(SRCS:%.c=%.o)

$(NAME) : $(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBS)

all : $(NAME)

clean : 

		$(RM) $(OBJS)

fclean : clean
		 $(RM) $(NAME)

re : fclean all
