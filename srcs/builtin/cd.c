/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:28:31 by maw               #+#    #+#             */
/*   Updated: 2025/04/18 16:45:00 by masase           ###   ########.fr       */
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
	printf("on va return VALID\n");
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
		printf("on est dans le open dir\n");
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
	printf("on va free le path\n");	
	free (path);
	return (VALID);
}

void	findvar_replace(t_shell *shell, char *buffer)
{
	int		i;

	i = 0;
	if (shell->path.oldpwd)
		free(shell->path.oldpwd);
	if (shell->path.pwd)
		shell->path.oldpwd = ft_strjoin("OLD" ,shell->path.pwd);
	if (shell->path.pwd)
		free(shell->path.pwd);
	buffer = getcwd(NULL, 0);
	shell->path.pwd = ft_strjoin("PWD=", buffer);
	free(buffer);
	while (shell->env[i] && strncmp(shell->env[i], "PWD=", 4) != 0)
		i++;
	if (shell->env[i] != NULL)
	{
		printf("on remet un pwd\n");
		free(shell->env[i]);
		shell->env[i] = ft_strdup(shell->path.pwd);
	}
	i = 0;
	while (shell->env[i] && strncmp(shell->env[i], "OLDPWD=", 7) != 0)
		i++;
	printf("le old trouve: %s", shell->env[i]);
	if (shell->env[i] != NULL)
	{
		printf("on remet un oldpwd\n");
		free(shell->env[i]);
		shell->env[i] = ft_strdup(shell->path.oldpwd);
	}
}

void	put_oldpwd(int i, t_shell *shell, char *temp)
{
	shell->env = ft_realloc(shell->env, i * sizeof(char *),
			(i + 1) * sizeof(char *));
	shell->env[i] = ft_strjoin("OLD", temp);
	i++;
	shell->env[i] = NULL;
}
