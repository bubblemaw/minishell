/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:12:05 by david             #+#    #+#             */
/*   Updated: 2025/02/11 14:27:38 by dchellen         ###   ########.fr       */
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

typedef struct s_list
{
	char 			*value;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;


typedef struct s_shell
{
	t_list			*head;
}	t_shell;

#endif
