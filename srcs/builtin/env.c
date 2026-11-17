/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:14:29 by maw               #+#    #+#             */
/*   Updated: 2025/04/23 09:28:33 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	if (cmd->arg[1])
	{
		error("too much arguments");
		shell->exit_status = 1;
		return (VALID);
	}
	if (!shell->env)
	{
		printf("env vide\n");
		return (ERROR);
	}
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	shell->exit_status = 0;
	return (VALID);
}
