/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:17:30 by maw               #+#    #+#             */
/*   Updated: 2025/03/03 19:20:26 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../FT_PRINTF/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include "../GNL/get_next_line.h"

typedef struct s_tok
{
	char *str;
	int type;
	struct s_tok *next;
	struct s_tok *prev;
}	t_tok;

typedef struct s_node {
    char *str;
    int type;
    struct s_node *prev;
    struct s_node *next;
} t_node;

typedef struct s_cmd
{
	char **arg;
	char *infile; 
	char *outfile;
	char *delimiter;
	int	append;
	int type;// pipe or delimiter
	struct s_token *next;
}	t_cmd;

typedef struct s_shell
{
	char **env;
	int STDIN;
	int STDOUT;
	int STDERR;
	int prev_pipefd;
	int here_fd;
	
}	t_shell;

# define PARENT_PROCESS 1
# define CHILD_PROCESS 2
# define PIPE 1
# define DELIMITER 2
# define NOTHING 0
# define CMD 1
# define OPTION 2
# define ARG 3
# define REDIRECTION 4
# define SQ 5
# define DQ 6


t_cmd *create_cmd(char **arg, char *infile, char *outfile, char *delimiter, int append, int type);
void add_cmd(t_cmd **head, char **arg, char *infile, char *outfile, char *delimiter, int append, int type);
void print_cmds(t_cmd *head);
void free_cmds(t_cmd *head);
char	*ft_parse(t_cmd *cmd);
char	*ft_cmd_path(t_cmd *cmd);
char	*join_path(char **tab_path, t_cmd *cmd);
void	free_tab(char **tab);
int ft_direction(t_cmd *token);
int ft_execute(t_cmd *token, t_shell *shell);
int ft_exe(t_cmd *token);
void reset_fd(t_shell *shell);
void save_fd(t_shell *shell);
int piper(t_cmd *cmd, t_shell *shell);
int ft_exe_pipe(t_cmd *token);
int lst_size(t_cmd *token);
int		error(char *str);
void init_execution(t_shell *shell, char **env);
int child_processor(t_shell *shell, t_cmd *cmd, int *pipefd);
int here_doc(t_cmd *token, t_shell *shell);
int	built_in(t_cmd *token);
int	echo(t_cmd *token);
int ft_expansion(t_node *node, t_shell *shell);
int expansion(t_node *node, t_shell *shell);
char *ft_findvar(char *var_name, t_shell *shell);
void *ft_realloc(void *ptr, size_t new_size);


#endif