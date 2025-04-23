/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:59:10 by maw               #+#    #+#             */
/*   Updated: 2025/04/23 08:51:10 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_parse(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (ft_strnstr(cmd->arg[0], "bin", ft_strlen(cmd->arg[0])) != NULL)
		cmd_path = cmd->arg[0];
	else if (ft_strncmp("./", cmd->arg[0], 2) == 0)
	{
		cmd_path = ft_strjoin(getcwd(NULL, 0), "/");
		cmd_path = ft_strjoin(cmd_path, cmd->arg[0]);
	}
	else if (ft_strnstr(cmd->arg[0], "/", ft_strlen(cmd->arg[0])) != NULL)
		cmd_path = cmd->arg[0];
	else
		cmd_path = ft_cmd_path(cmd, shell);
	return (cmd_path);
}

char	*ft_cmd_path(t_cmd *cmd, t_shell *shell)
{
	char	**tab_path;
	char	*path;
	char	*env;
	int		i;

	i = 0;
	while (shell->env[i] && ft_strncmp(shell->env[i], "PATH", 4) != 0)
		i++;
	if (!shell->env[i])
		return (NULL);
	env = ft_strdup(shell->env[i]);
	tab_path = ft_split(env, ':');
	if (tab_path == NULL)
		return (NULL);
	free(env);
	path = join_path(tab_path, cmd);
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*join_path(char **tab_path, t_cmd *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (tab_path[i])
	{
		tmp = ft_strjoin(tab_path[i], "/");
		path = ft_strjoin(tmp, cmd->arg[0]);
		free(tmp);
		if (access(path, F_OK) == 0)
		{
			free_tab(tab_path);
			return (path);
		}
		free(path);
		path = NULL;
		i++;
	}
	free_tab(tab_path);
	return (NULL);
}
