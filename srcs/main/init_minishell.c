/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:31:21 by maw               #+#    #+#             */
/*   Updated: 2025/04/23 09:33:18 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_execution(t_shell *shell)
{
	shell->prev_pipefd = -1;
	save_fd(shell);
	shell->cmd = NULL;
	shell->exit_status = 0;
	shell->invalid_redir = 0;
	free_new_redirection(shell);
}

char	**copy_env(char **env)
{
	int		env_size;
	int		i;
	char	**copy_env;

	env_size = 0;
	while (env[env_size])
		env_size++;
	copy_env = malloc((env_size + 1) * sizeof(char *));
	if (!copy_env)
		return (NULL);
	i = 0;
	while (i < env_size)
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

void	init_shell(t_shell *shell)
{
	shell->crash.prev = NULL;
	shell->crash.new_var = NULL;
	shell->crash.tmp = NULL;
	shell->creat.content = NULL;
	shell->creat.first = NULL;
	shell->creat.err = NULL;
	shell->exp.new = NULL;
	shell->exp.sub_env = NULL;
	shell->exp.tmp = NULL;
	shell->exp.tmp_2 = NULL;
	shell->exp.tmp_3 = NULL;
	shell->exp.add = NULL;
	shell->exp.line = NULL;
	shell->exp.tab = NULL;
	shell->exp.temp = NULL;
	shell->kill.new = NULL;
	shell->kill.tmp = NULL;
	shell->kill.stash = NULL;
	shell->here_doc_expan = VALID;
	return ;
}

void	save_pwd(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i] && ft_strncmp(shell->env[i], "PWD=", 4) != 0)
		i++;
	if (shell->env[i] != NULL)
		shell->path.pwd = ft_strdup(shell->env[i]);
	i = 0;
	while (shell->env[i] && ft_strncmp(shell->env[i], "OLDPWD=", 7) != 0)
		i++;
	if (shell->env[i] != NULL)
		shell->path.oldpwd = ft_strdup(shell->env[i]);
}
