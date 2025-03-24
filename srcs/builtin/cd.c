/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:28:31 by maw               #+#    #+#             */
/*   Updated: 2025/03/24 15:58:52 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int cd(t_cmd *cmd, t_shell *shell)
{
	DIR *d;
	int i;
	char *temp;
	char *path;
	char buffer[1024];
	

	if (cmd->arg[1][0] == '/')
		path = ft_strdup(cmd->arg[1]);
	else
	{		
		getcwd(buffer, 1024);
		path = ft_strjoin(buffer, "/");
		path = ft_strjoin(path, cmd->arg[1]);
	}
	d = opendir(cmd->arg[1]);
	if (d)
	{
		if (chdir(path) == -1)
			perror(cmd->arg[1]);
		i = 0;
		while (shell->env[i] && strncmp(shell->env[i], "PWD", 3) != 0)
			i++;
		temp = ft_strdup(shell->env[i]);
		free(shell->env[i]);
		shell->env[i] = NULL;
		getcwd(buffer, 1024);
		shell->env[i] = ft_strjoin("PWD=", buffer);
		i = 0;
		while (shell->env[i] && strncmp(shell->env[i], "OLDPWD", 6) != 0)
			i++;
		free(shell->env[i]);
		shell->env[i] = NULL;
		shell->env[i] = ft_strjoin("OLD" ,temp);
		i++;
		shell->env[i] = NULL;
		free(temp);
		closedir(d);
	}
	else
		perror(cmd->arg[1]);
	return (VALID);
}
