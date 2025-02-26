/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:25:49 by maw               #+#    #+#             */
/*   Updated: 2025/02/26 18:06:41 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	echo(t_token *token)
{
	int flag_n;
	int i;

	i = 1;
	flag_n = 0;
	while (ft_strncmp(token->arg[i],"-n", 2) == 0)
	{
		flag_n = 1;
		i++;
	}
	while (token->arg[i])
	{
		ft_putstr_fd(token->arg[i], STDOUT_FILENO);
		if (token->arg[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}	
	if (flag_n == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}


