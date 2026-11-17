/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:01:13 by maw               #+#    #+#             */
/*   Updated: 2025/04/18 15:07:50 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*path_finder(t_cmd *cmd, char *buffer)
{
	char	*path;
	char	*temp;

	path = NULL;
	if (cmd->arg[1][0] == '/')
		path = ft_strdup(cmd->arg[1]);
	else
	{
		buffer = getcwd(NULL, 0);
		temp = ft_strjoin(buffer, "/");
		path = ft_strjoin(temp, cmd->arg[1]);
		free (temp);
		free (buffer);
	}
	return (path);
}

char	*find_user_name(char **tab)
{
	int		i;
	char	*path;

	i = 0;
	while (tab[i] && strncmp(tab[i], "USER=", 5))
		i++;
	if (tab[i] != NULL)
	{
		path = ft_strdup(tab[i] + 5);
	}
	return (path);
}
