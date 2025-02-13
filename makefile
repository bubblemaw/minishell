# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: masase <masase@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 00:38:47 by maw               #+#    #+#              #
#    Updated: 2025/02/13 14:19:08 by masase           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = pseudo_code.c \
		liste_chaine.c \
		search_cmd.c \

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





