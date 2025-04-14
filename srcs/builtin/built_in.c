/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:34:33 by maw               #+#    #+#             */
/*   Updated: 2025/04/14 21:48:35 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_in(t_cmd *cmd, t_shell *shell)
{
	if (ft_strlen(cmd->arg[0]) == 4 && ft_strncmp(cmd->arg[0], "echo", 4) == 0)
		return (echo(cmd));
	else if (ft_strlen(cmd->arg[0]) == 6
		&& ft_strncmp(cmd->arg[0], "export", 6) == 0)
	{
		if (export_check(shell) == ERROR)
			return (VALID);
		export(cmd, shell);
		return (VALID);
	}
	else if (ft_strlen(cmd->arg[0]) == 2
		&& ft_strncmp(cmd->arg[0], "cd", 2) == 0)
		return (cd(cmd, shell));
	else if (ft_strlen(cmd->arg[0]) == 3
		&& ft_strncmp(cmd->arg[0], "env", 3) == 0)
		return (ft_env(cmd, shell));
	else if (ft_strlen(cmd->arg[0]) == 3
		&& ft_strncmp(cmd->arg[0], "pwd", 3) == 0)
		return (pwd(shell));
	else if (ft_strlen(cmd->arg[0]) == 5
		&& ft_strncmp(cmd->arg[0], "unset", 5) == 0)
		return (unset(cmd, shell));
	else if (ft_strlen(cmd->arg[0]) == 4
		&& ft_strncmp(cmd->arg[0], "exit", 4) == 0)
	{
		ft_exit(cmd, shell);
		return (VALID);
	}
	return (ERROR);
}

int	export_check(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokken;
	while (ft_strncmp(tmp->value, "export", 6) != 0)
		tmp = tmp->next;
	ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
		return (ERROR);
	while (tmp != NULL)
	{
		if (tmp->type == OPTION || tmp->type == ARG)
		{
			ft_putstr_fd("Error export : write only variables\n",
				STDERR_FILENO);
			return (ERROR);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	built_in_pipe(t_cmd *cmd, t_shell *shell)
{
	int	result;

	result = ERROR;
	if (ft_strlen(cmd->arg[0]) == 4 && ft_strncmp(cmd->arg[0], "echo", 4) == 0)
		result = echo(cmd);
	else if (ft_strlen(cmd->arg[0]) == 6
		&& ft_strncmp(cmd->arg[0], "export", 6) == 0)
		result = export(cmd, shell);
	else if (ft_strlen(cmd->arg[0]) == 2
		&& ft_strncmp(cmd->arg[0], "cd", 2) == 0)
		result = cd(cmd, shell);
	else if (ft_strlen(cmd->arg[0]) == 3
		&& ft_strncmp(cmd->arg[0], "env", 3) == 0)
		result = ft_env(cmd, shell);
	else if (ft_strlen(cmd->arg[0]) == 3
		&& ft_strncmp(cmd->arg[0], "pwd", 3) == 0)
		result = pwd(shell);
	else if (ft_strlen(cmd->arg[0]) == 5
		&& ft_strncmp(cmd->arg[0], "unset", 5) == 0)
		result = unset(cmd, shell);
	else if (ft_strlen(cmd->arg[0]) == 4
		&& ft_strncmp(cmd->arg[0], "exit", 4) == 0)
		ft_exit(cmd, shell);
	if (result == VALID)
	{
		g_exit_status = 0;
		exit (0);
	}
	return (result);
}
