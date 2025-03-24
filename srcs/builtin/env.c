/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:14:29 by maw               #+#    #+#             */
/*   Updated: 2025/03/24 00:00:43 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_cmd *cmd, t_shell *shell)
{
	int i;

	i = 0;
	(void)cmd;
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
	return (VALID);
}