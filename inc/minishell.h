/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:04:10 by maw               #+#    #+#             */
/*   Updated: 2025/03/10 14:11:10 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../GNL/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// command's return
# define ERROR 2
# define VALID 1

// execution return
# define PARENT_PROCESS 1
# define CHILD_PROCESS 2
# define DELIMITER 20

// parsing's type data
typedef enum 
{
	NAME,         // 0
	EQUALITY,     // 1
	VALUE,        // 2
	COMMAND,      // 3
	REDIRECTION,  // 4
	PIPE,         // 5
	ARGUMENT,	  // 6
	OPTION		  // 7
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

// structure command's list
typedef struct s_cmd
{
	char **arg;
	char *infile;
	char *outfile;
	char *delimiter;
	int	append;
	int	type;// pipe or delimiter
	struct s_cmd *next;
}	t_cmd;

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
	bool			find;
	t_token			*new;
}	t_creat;

// principal struct
typedef struct s_shell
{
	char **env;
	int STDIN;
	int STDOUT;
	int STDERR;
	int prev_pipefd;
	int here_fd;
	t_cmd *cmd;
	char			*input;
	t_creat			creat;
	t_token			*tokken;

}	t_shell;

// token's fonctions
int		enter_input(t_shell *shell);
int		creat_tokken(char *input, t_shell *shell);
int		skip_space(char *str, int *i);
int		double_quotes(char *str, int *i);
int		single_quotes(char *str, int *i);
int		detect_redirections(char *str, int *i);
int		detect_variables(bool *var, char *str, int *i);
int		detect_var_value(char *input, int *i);
int		detect_command(char *input, int *i);

// token's parsing
int		creat_list(t_shell *shell, char *input);
void	give_token_data(t_shell *shell);

// fonctions to creat list
t_token	*creat_node(char *content);
void	add_node(t_shell *shell, t_token *new);
void	free_list(t_token *head);
void	print_token(t_token *head);

// recherche commande et chemin
char	*ft_parse(t_cmd *cmd, t_shell *shell);
char	*ft_cmd_path(t_cmd *cmd, t_shell *shell);
char	*join_path(char **tab_path, t_cmd *cmd);

// redirection
int		ft_direction(t_cmd *token);
void	reset_fd(t_shell *shell);
void	save_fd(t_shell *shell);

// execution
int		ft_execute(t_shell *shell);
int		ft_exe(t_cmd *token, t_shell *shell);
int		built_in(t_cmd *token);
int		echo(t_cmd *token);

// token list -> cmd list
t_cmd	*end_list(t_cmd *head);
int		ft_cmd_maker(t_cmd *cmd, t_token **tokken);
int		ft_cmd_pipe(t_cmd *cmd);
int		ft_cmd_redirection(t_cmd *cmd, t_token **tokken);
void	*ft_realloc(void *ptr,size_t old_size, size_t new_size);
void	add_cmd_lst(t_cmd **head);
int		create_cmd_lst(t_shell *shell);
void	setup_cmd_lst(t_cmd *cmd);
void	print_cmds(t_cmd *head);

// pipe
int		piper(t_cmd *cmd, t_shell *shell);
int		ft_exe_pipe(t_cmd *token, t_shell *shell);
int		lst_size(t_cmd *token);
int		child_processor(t_cmd *cmd, t_shell *shell, int *pipefd);
int		here_doc(t_cmd *cmd, t_shell *shell);

// expansion
int		ft_expansion(t_shell *shell);
int		expansion(t_token *tokken, t_shell *shell);
char	*ft_findvar(char *var_name, t_shell *shell);
int		is_double_quote(t_token *tokken);


//init_minishell
void	init_execution(t_shell *shell, char **env);
char	**copy_env(char **env);

// free
void	free_tab(char **tab);
void	free_shell(t_shell *shell);
void	free_cmds(t_cmd **head);
void	free_tab(char **tab);

// error
int		error_cmd(char *str, t_shell *shell);
int		error(char *str);

#endif
