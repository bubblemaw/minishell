/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:04:10 by maw               #+#    #+#             */
/*   Updated: 2025/04/02 14:20:53 by maw              ###   ########.fr       */
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
# include <dirent.h>
# include <signal.h>

// command's return
# define DOUBLE 3
# define ERROR 2
# define VALID 1

// execution return
# define PARENT_PROCESS 1
# define CHILD_PROCESS 2
# define DELIMITER 20

// global variable
extern int g_exit_status;

// parsing's type data
typedef enum 
{
	NAME,
	EQUALITY,
	VALUE,
	COMMAND,
	REDIRECTION,
	PIPE,
	ARGUMENT,
	OPTION
} type;

// structures
// variables's struct without export
typedef struct s_var
{
	char		*name;
	char 		*value;
	struct s_var *next;
}	t_var;

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
	struct s_cmd *prev;
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

	int				start;
	int				len;

	t_token			*new;
	t_var			*new_var;
}	t_creat;

typedef struct s_redir
{
	char *prev_infile;
	char *prev_outfile;
	char *prev_delimiter;
	int apppend;
	int type;
}	t_redir;

typedef struct s_utils
{
	int		size_var;
	char	*new_arg;
	char	*sub_env;
}	t_utils;

// principal struct
typedef struct s_shell
{
	char **env;
	int STDIN;
	int STDOUT;
	int STDERR;
	int prev_pipefd;
	int	exit_status;
	t_redir			redir;
	int here_fd;
	t_cmd *cmd;
	char			*input;
	t_creat			creat;
	t_token			*tokken;
	t_var			*var;
	t_utils			utils;
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
int		outfile_direction(t_cmd *cmd);
void	reset_fd(t_shell *shell);
void	save_fd(t_shell *shell);
int		here_doc(t_cmd *cmd, t_shell *shell);
void	here_doc_child_process(int *pipefd, t_cmd *cmd);

// execution
int		ft_execute(t_shell *shell);
int		ft_exe(t_cmd *token, t_shell *shell);
int		wait_exit_status(t_shell *shell, int *pipe_exit_flag);
int		built_in(t_cmd *cmd, t_shell *shell);

// built in fonctions
int		export(t_cmd *token, t_shell *shell);
int		echo(t_cmd *cmd);
int		echo_option(t_cmd *cmd);
int		cd(t_cmd *cmd, t_shell *shell);
char	*path_finder(t_cmd *cmd, char *buffer);
void	findvar_replace(t_shell *shell, char *buffer);
char	*find_user_name(char **tab);
int		ft_env(t_cmd *cmd, t_shell *shell);
int		pwd(void);
int		unset(t_cmd *cmd, t_shell *shell);
int		ft_strlen_to_equal(char *str);
int		slide_tab(char **tab, int i);
void	ft_exit(t_cmd *cmd, t_shell *shell);
int		is_arguments_digit(char **tab);

// token list -> cmd list
t_cmd	*end_list(t_cmd *head);
int		ft_cmd_maker(t_cmd *cmd, t_token **tokken);
int		ft_cmd_pipe(t_cmd *cmd, t_token **tokken);
int		ft_cmd_redirection(t_cmd *cmd, t_token **tokken, t_shell *shell);
void	simple_redirection(t_cmd *cmd, t_token **tokken, t_shell *shell);
void	double_redirection(t_cmd *cmd, t_token **tokken, t_shell *shell);
void	*ft_realloc(void *ptr,size_t old_size, size_t new_size);
void	add_cmd_lst(t_cmd **head);
void	add_cmd_before_last(t_cmd **head);
int		create_cmd_lst(t_shell *shell);
void	setup_cmd_lst(t_cmd **cmd);
void	print_cmds(t_cmd **head);
int		new_cmd(t_cmd **head_cmd, t_cmd **current);
int		new_cmd_redirection(t_cmd **head_cmd, t_shell *shell);
void	save_outfile(t_shell *shell, t_cmd *cmd);
void	save_infile(t_shell *shell, t_cmd  *cmd);
void	save_delimiter(t_shell *shell, t_cmd *cmd);
void	insert_node(t_cmd *current, t_cmd *new_cmd);

// pipe
int		piper(t_cmd *cmd, t_shell *shell);
void	pipex_loop(t_cmd *current, t_shell *shell);
int		ft_exe_pipe(t_cmd *token, t_shell *shell);
int		lst_size(t_cmd *token);
int		child_processor(t_cmd *cmd, t_shell *shell, int *pipefd);

// expansion
// local gestion
int		init_var_local(t_shell *shell);
t_var	*check_doubles(t_var *check, char *name);
void	replace_var(t_var *exist_var, t_token *temp);
int		crush_export_var(t_shell *shell, char *name, char *value);
void	creat_var_list(t_shell *shell, t_token *temp);
t_var	*creat_node_var(char *name, char *content);
void	add_node_var(t_shell *shell, t_var *new);
void	free_list_var(t_var *head);
void	print_var_local(t_var *head);
// export gestion
int		join_var(t_token **token);
int		check_double_export(char *var, t_shell *shell);
int		crush_local_var(t_shell *shell, char *var);

int		specials_case(t_shell  *shell, char *current);
int		pid_dolls(t_shell  *shell, char *current);
int		ft_expansion(t_shell *shell);
int		find_var(t_shell  *shell, t_token *current);
int		search_export_var(t_shell *shell, char* str);
int		search_local_var(t_shell *shell, char* str, t_var *temp);
int		var_size(char *str);
int		is_double_quote(t_token *tokken);
int		kill_quotes(t_shell *shell);
void	size_to_kill(t_token *token, t_shell *shell, int *i);

// variables priorities
void	crush_var(t_shell *shell);

//init_minishell
void	init_execution(t_shell *shell);
char	**copy_env(char **env);

// signal
void	signalhandler(int signal);
void	signalhandler_heredoc(int signal);
void	ft_exit_void(int n,t_shell *shell);

// free
void	free_tab(char **tab);
void	free_shell(t_shell *shell);
void	free_cmds(t_cmd **head);
void	free_tab(char **tab);
int		free_new_redirection(t_shell *shell);

// error
int		error_cmd(char *str);
int		error(char *str);
int		error_exit(char *str);

#endif
