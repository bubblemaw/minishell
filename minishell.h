/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:17:30 by maw               #+#    #+#             */
/*   Updated: 2025/02/13 11:22:23 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
	struct s_cmd *next;
}	t_cmd;

t_cmd *create_cmd(char **arg, char *infile, char *outfile, int append);
void add_cmd(t_cmd **head, char **arg, char *infile, char *outfile, int append);
void print_cmds(t_cmd *head);
void free_cmds(t_cmd *head);
int	ft_parse(t_cmd *cmd);
char	*ft_cmd_path(t_cmd *cmd);
char	*join_path(char **tab_path, t_cmd *cmd);


#endif