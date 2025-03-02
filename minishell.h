/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:12:05 by david             #+#    #+#             */
/*   Updated: 2025/03/03 17:06:09 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

// command's return
# define ERROR 2
# define VALID 1

// parsing's type data
typedef enum 
{
	COMMAND,
	SINGLE_Q,
	DOUBLE_Q,
	REDIRECTION,
	EQUALITY,
	PIPE,
	ARGUMENT,
	OPTION
} type;

// structures
// structure for the chain
typedef struct s_token
{
	char 			*value;
	struct s_token	*prev;
	struct s_token	*next;
	type			type;
}	t_token;

//for the parse when the tokens are creat
typedef struct s_creat
{
	int				i;
	int				begin;
	int				end;
	char			*content;
	char			*last_token;
	int				result;
	bool			var;
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
int		handle_quotes(char *input, int *i);
int		double_quotes(char *str, int *i);
int		single_quotes(char *str, int *i);
int		detect_redirections(char *str, int *i);
int		detect_variables(bool *var, char *str, int *i);
int		detect_command(char *input, int *i);

// token's parsing
int		creat_list(t_shell *shell, char *input);
void	give_token_data(t_shell *shell);

// fonctions to creat list
t_token	*creat_node(char *content);
void	add_node(t_shell *shell, t_token *new);
void	free_list(t_token *head);
void	print_token(t_token *head);

#endif
