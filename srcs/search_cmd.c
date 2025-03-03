/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:35:59 by maw               #+#    #+#             */
/*   Updated: 2025/03/03 15:50:15 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

char	*ft_parse(t_cmd *cmd)
{
	//est-ce qu'on passe par un chemin absolu
	//est-ce que on va chercher la commande dans
	//le PATH
	char *cmd_path;
	char	c;

	c = '/';
	cmd_path = NULL;
	if (ft_strnstr(cmd->arg[0], "bin", ft_strlen(cmd->arg[0])) != NULL)
	{
		cmd_path = cmd->arg[0];
		cmd->arg = ft_split(ft_strnstr(cmd->arg[0], "bin", ft_strlen(cmd->arg[0])) + 4, c);
	}
	else
			cmd_path = ft_cmd_path(cmd);		
	// else
	// 	cmd->arg = ft_split(cmd, c);
	// cmd->cmd_path = ft_cmd_path(cmd);
	// if (child->cmd_path == NULL)
	// {
	// 	error_cmd(child->cmd_arg[0]);
	// 	free_tab(child->cmd_arg);
	// 	child->cmd_arg = NULL;
	// 	exit(EXIT_SUCCESS);
	// }
	return (cmd_path);
}

char	*ft_cmd_path(t_cmd *cmd)
{
	char	**tab_path;
	char	*path;
	char	*env;

	env = getenv("PATH");
	if (!env)
		return (NULL);
	tab_path = ft_split(env, ':');
	if (tab_path == NULL)
		return (NULL);
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