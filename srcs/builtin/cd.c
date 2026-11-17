/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:28:31 by maw               #+#    #+#             */
/*   Updated: 2025/04/23 09:23:42 by dchellen         ###   ########.fr       */
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
		shell->exit_status = 1;
		return (VALID);
	}
	else
		path = path_finder(cmd, buffer);
	if (move_into_dir(cmd, shell, path) == ERROR)
		shell->exit_status = 1;
	else
		shell->exit_status = 0;
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
		shell->exit_status = 1;
		free (path);
		return (ERROR);
	}
	free (path);
	return (VALID);
}

void	findvar_replace(t_shell *shell, char *buffer)
{
	int	i;

	i = 0;
	update_pwd(shell);
	buffer = getcwd(NULL, 0);
	shell->path.pwd = ft_strjoin("PWD=", buffer);
	free(buffer);
	while (shell->env[i] && ft_strncmp(shell->env[i], "PWD=", 4) != 0)
		i++;
	if (shell->env[i] != NULL)
	{
		free(shell->env[i]);
		shell->env[i] = ft_strdup(shell->path.pwd);
	}
	i = 0;
	while (shell->env[i] && ft_strncmp(shell->env[i], "OLDPWD=", 7) != 0)
		i++;
	if (shell->env[i] != NULL)
	{
		free(shell->env[i]);
		shell->env[i] = ft_strdup(shell->path.oldpwd);
	}
}

void	update_pwd(t_shell *shell)
{
	if (shell->path.oldpwd)
		free(shell->path.oldpwd);
	if (shell->path.pwd)
		shell->path.oldpwd = ft_strjoin("OLD", shell->path.pwd);
	if (shell->path.pwd)
		free(shell->path.pwd);
}
