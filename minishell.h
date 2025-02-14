/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:17:30 by maw               #+#    #+#             */
/*   Updated: 2025/02/14 17:00:32 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "FT_PRINTF/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_cmd
{
	char **arg;
	char *infile; 
	char *outfile;
	int	append;
	int type;
	struct s_cmd *next;
}	t_cmd;

t_cmd *create_cmd(char **arg, char *infile, char *outfile, int append, int type);
void add_cmd(t_cmd **head, char **arg, char *infile, char *outfile, int append, int type);
void print_cmds(t_cmd *head);
void free_cmds(t_cmd *head);
char	*ft_parse(t_cmd *cmd);
char	*ft_cmd_path(t_cmd *cmd);
char	*join_path(char **tab_path, t_cmd *cmd);
// int execute_cmd(t_cmd *cmd, int *leftfd, int *rightfd);
void	free_tab(char **tab);
int execute_cmd(t_cmd *cmd, int input_fd, int output_fd);


#endif