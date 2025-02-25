/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:12:05 by david             #+#    #+#             */
/*   Updated: 2025/02/25 18:11:14 by dchellen         ###   ########.fr       */
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

// command's return
# define ERROR 2
# define VALID 1

// parsing's type data
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

// structures
// structure for the chain
typedef struct s_token
{
	char 			*value;
	struct s_token	*prev;
	struct s_token	*next;
	int				type;
}	t_token;

//for the parse when the tokens are creat
typedef struct s_creat
{
	int				i;
	int				begin;
	int				end;
	char			*content;
	char			*last_token;
	int				result_d;
	int				result_s;
	t_token			*new;
}	t_creat;

// principal struct
typedef struct s_shell
{
	char			*input;
	t_creat			creat;
	t_token			*tokken;

}	t_shell;

// token's fonctions
int		creat_tokken(char *input, t_shell *shell);
int		skip_space(char *str, int *i);
int		double_quotes(char *str, int *i);
int		single_quotes(char *str, int *i);
int		detect_redirections(char *str, int *i);
int		detect_command(char *input, int *i);

// token's parsing
int		creat_list(t_shell *shell, char *input);

// fonctions to creat list
t_token	*creat_node(char *content);
void	add_node(t_shell *shell, t_token *new);
void	free_list(t_token *head);
void	print_token(t_token *head);

#endif
