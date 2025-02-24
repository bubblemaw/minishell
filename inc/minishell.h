/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:17:30 by maw               #+#    #+#             */
/*   Updated: 2025/02/24 18:33:10 by masase           ###   ########.fr       */
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

typedef struct s_token
{
	char **arg;
	char *infile; 
	char *outfile;
	char *delimiter;
	int	append;
	int type;
	struct s_token *next;
}	t_token;

typedef struct s_shell
{
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

// # define NOTHING 0
// # define CMD 1
// # define ARG 2
// # define OUTFD 3
// # define INFD 4


t_token *create_cmd(char **arg, char *infile, char *outfile, int append, int type);
void add_cmd(t_token **head, char **arg, char *infile, char *outfile, char *delimiter, int append, int type);
void print_cmds(t_token *head);
void free_cmds(t_token *head);
char	*ft_parse(t_token *cmd);
char	*ft_cmd_path(t_token *cmd);
char	*join_path(char **tab_path, t_token *cmd);
void	free_tab(char **tab);
int ft_direction(t_token *token);
int ft_execute(t_token *token, t_shell *shell);
int ft_exe(t_token *token);
void reset_fd(t_shell *shell);
void save_fd(t_shell *shell);
int piper(t_token *cmd, t_shell *shell);
int ft_exe_pipe(t_token *token);
int lst_size(t_token *token);
int		error(char *str);
void init_execution(t_shell *shell);
int child_processor(t_shell *shell, t_token *cmd, int *pipefd);
int here_doc(t_token *token, t_shell *shell);

#endif