/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:28:31 by maw               #+#    #+#             */
/*   Updated: 2025/04/02 11:44:28 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cd(t_cmd *cmd, t_shell *shell)
{
	DIR		*d;
	char	*path;
	char	*buffer;
	
	buffer = NULL;
	if (cmd->arg[1] == NULL || (ft_strncmp(cmd->arg[1], "~", 1) == 0 && ft_strlen(cmd->arg[1]) == 1))
		path = ft_strjoin("/home/", find_user_name(shell->env));
	else if (cmd->arg[2])
	{
		error("too much arguments");
		g_exit_status = 1;
		return (VALID);
	}
	else
		path = path_finder(cmd, buffer);
	d = opendir(path);
	if (d)
	{
		if (chdir(path) == -1)
			perror(cmd->arg[1]);
		findvar_replace(shell, buffer);
		closedir(d);
	}
	else
	{
		perror(cmd->arg[1]);
		g_exit_status = 1;
	}
	free (path);
	return (VALID);
}

char	*path_finder(t_cmd *cmd, char *buffer)
{
	char	*path;

	path = NULL;
	if (cmd->arg[1][0] == '/')
		path = ft_strdup(cmd->arg[1]);
	else
	{		
		buffer = getcwd(NULL, 0);
		path = ft_strjoin(buffer, "/");
		path = ft_strjoin(path, cmd->arg[1]);
	}
	return (path);
}

void	findvar_replace(t_shell *shell, char *buffer)
{
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	while (shell->env[i] && strncmp(shell->env[i], "PWD", 3) != 0)
		i++;
	temp = ft_strdup(shell->env[i]);
	free(shell->env[i]);
	shell->env[i] = NULL;
	buffer = getcwd(NULL, 0);
	shell->env[i] = ft_strjoin("PWD=", buffer);
	i = 0;
	while (shell->env[i] && strncmp(shell->env[i], "OLDPWD", 6) != 0)
		i++;
	if (shell->env != NULL)
	{
		free(shell->env[i]);
		shell->env[i] = NULL;
	}
	shell->env[i] = ft_strjoin("OLD" ,temp);
	i++;
	shell->env[i] = NULL;
	free(temp);
}

char	*find_user_name(char **tab)
{
	int		i;
	char	*path;

	i = 0;
	while(tab[i] && strncmp(tab[i], "USER=", 5))
		i++;
	if (tab[i] != NULL)
	{
		path = ft_strdup(tab[i] + 5);
	}
	return (path);
}
