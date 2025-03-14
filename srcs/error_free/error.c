/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:00:12 by maw               #+#    #+#             */
/*   Updated: 2025/03/14 14:59:08 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int error_cmd(char *str, t_shell *shell)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd("Command not found: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	free_shell(shell);
	// (void)shell;
	exit (EXIT_SUCCESS);
}
