/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:28:31 by maw               #+#    #+#             */
/*   Updated: 2025/04/18 13:35:25 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	*buffer;

	buffer = NULL;
	if (cmd->arg[1] == NULL || (ft_strncmp(cmd->arg[1], "~", 1) == 0
			&& ft_strlen(cmd->arg[1]) == 1))
	{
		buffer = find_user_name(shell->env);
		path = ft_strjoin("/home/", buffer);
		free (buffer);
	}
	else if (cmd->arg[2])
	{
		error("too much arguments");
		g_exit_status = 1;
		return (VALID);
	}
	else
		path = path_finder(cmd, buffer);
	if (move_into_dir(cmd, shell, path) == ERROR)
		g_exit_status = 1;
	else
		g_exit_status = 0;
	return (VALID);
}

int	move_into_dir(t_cmd *cmd, t_shell *shell, char *path)
{
	DIR		*d;
	char	*buffer;

	buffer = NULL;
	(void)shell;
	d = opendir(path);
	if (d)
	{
		if (chdir(path) == -1)
			perror(cmd->arg[1]);
		else
			findvar_replace(shell, buffer);
		closedir(d);
	}
	else
	{
		perror(cmd->arg[1]);
		g_exit_status = 1;
		free (path);
		return (ERROR);
	}
	free (path);
	return (VALID);
}

void	findvar_replace(t_shell *shell, char *buffer)
{
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	while (shell->env[i] && strncmp(shell->env[i], "PWD=", 4) != 0)
		i++;
	if (shell->env[i] != NULL)
	{
		temp = ft_strdup(shell->env[i]);
		free(shell->env[i]);
		shell->env[i] = NULL;
		buffer = getcwd(NULL, 0);
		shell->env[i] = ft_strjoin("PWD=", buffer);
		free(buffer);
	}
	i = 0;
	while (shell->env[i] && strncmp(shell->env[i], "OLDPWD=", 7) != 0)
		i++;
	if (shell->env != NULL)
	{
		free(shell->env[i]);
		shell->env[i] = NULL;
		shell->env[i] = ft_strjoin("OLD", temp);
		free(temp);
		temp = NULL;
	}
	if (temp)
		free(temp);
}

void	put_oldpwd(int i, t_shell *shell, char *temp)
{
	shell->env = ft_realloc(shell->env, i * sizeof(char *),
			(i + 1) * sizeof(char *));
	shell->env[i] = ft_strjoin("OLD", temp);
	i++;
	shell->env[i] = NULL;
}
