/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:12:05 by david             #+#    #+#             */
/*   Updated: 2025/02/22 11:25:15 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ERROR 2
# define VALID 1

# define COMMAND
# define SINGLE_Q
# define DOUBLE_Q
# define RED_L
# define RED_DL
# define RED_R
# define RED_DR
# define EQUAL
# define PIPE
# define ARG
# define OPTION

typedef struct s_chain
{
	char 			*value;
	struct s_chain	*prev;
	struct s_chain	*next;
	int				type;
}	t_chain;

typedef struct s_shell
{
	t_chain			*tokken;
}	t_shell;

#endif
