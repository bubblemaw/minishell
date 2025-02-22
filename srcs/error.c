/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:00:12 by maw               #+#    #+#             */
/*   Updated: 2025/02/20 17:39:08 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		error(char *str)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if(errno)
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	else
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit (EXIT_FAILURE);
}
