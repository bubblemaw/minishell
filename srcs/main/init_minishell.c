/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:31:21 by maw               #+#    #+#             */
/*   Updated: 2025/03/31 17:40:13 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void init_execution(t_shell *shell)
{
	shell->prev_pipefd = -1;
	save_fd(shell);
	shell->cmd = NULL;
	shell->exit_status = 0;
	free_new_redirection(shell);
}

char **copy_env(char **env)
{
	int	env_size;
	int i;
	char **copy_env;

	env_size = 0;
	while (env[env_size])
		env_size++;
	copy_env = malloc((env_size + 1) * sizeof(char *));
	if (!copy_env)
		return (NULL);
	i = 0;
	while(i < env_size)
	{
		copy_env[i] = ft_strdup(env[i]);
		if (copy_env[i] == NULL)
		{
			free_tab(copy_env);
			return (NULL);
		}
		i++;
	}
	copy_env[i] = NULL;
	return (copy_env);
}
