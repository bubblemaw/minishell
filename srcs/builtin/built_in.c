/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:34:33 by maw               #+#    #+#             */
/*   Updated: 2025/04/23 09:25:55 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_in(t_cmd *cmd, t_shell *shell)
{
	if (ft_strlen(cmd->arg[0]) == 4 && ft_strncmp(cmd->arg[0], "echo", 4) == 0)
		return (echo(cmd, shell));
	else if (ft_strlen(cmd->arg[0]) == 6
		&& ft_strncmp(cmd->arg[0], "export", 6) == 0)
	{
		export(cmd, shell);
		return (VALID);
	}
	else if (ft_strncmp(cmd->arg[0], "cd", 3) == 0)
		return (cd(cmd, shell));
	else if (ft_strncmp(cmd->arg[0], "env", 4) == 0)
		return (ft_env(cmd, shell));
	else if (ft_strncmp(cmd->arg[0], "pwd", 4) == 0)
		return (pwd(shell));
	else if (ft_strncmp(cmd->arg[0], "unset", 6) == 0)
		return (unset(cmd, shell));
	else if (ft_strncmp(cmd->arg[0], "exit", 5) == 0)
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
	while (tmp != NULL)
	{
		if (tmp->type == OPTION || tmp->type == ARG)
			tmp = tmp->next;
		else
		{
			if (tmp->type == NAME && var_name(tmp->value) == ERROR)
				ft_putstr_fd("export: has a invalid identifier\n",
					STDERR_FILENO);
			tmp = tmp->next;
		}
	}
	return (0);
}

int	built_in_pipe(t_cmd *cmd, t_shell *shell)
{
	int	result;

	result = ERROR;
	if (ft_strncmp(cmd->arg[0], "echo", 5) == 0)
		result = echo(cmd, shell);
	else if (ft_strncmp(cmd->arg[0], "export", 7) == 0)
		result = export(cmd, shell);
	else if (ft_strncmp(cmd->arg[0], "cd", 3) == 0)
		result = cd(cmd, shell);
	else if (ft_strncmp(cmd->arg[0], "env", 4) == 0)
		result = ft_env(cmd, shell);
	else if (ft_strncmp(cmd->arg[0], "pwd", 4) == 0)
		result = pwd(shell);
	else if (ft_strncmp(cmd->arg[0], "unset", 6) == 0)
		result = unset(cmd, shell);
	else if (ft_strncmp(cmd->arg[0], "exit", 5) == 0)
		ft_exit(cmd, shell);
	if (result == VALID)
	{
		shell->exit_status = 0;
		exit (0);
	}
	return (result);
}
