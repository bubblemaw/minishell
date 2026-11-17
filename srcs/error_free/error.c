/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:00:12 by maw               #+#    #+#             */
/*   Updated: 2025/04/23 09:31:07 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	error(char *str)
{
	char	*error;

	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (errno)
	{
		error = malloc((ft_strlen(str)
					+ ft_strlen(strerror(errno)) + 3) * sizeof(char));
		error = ft_strjoin(error, str);
		error = ft_strjoin(error, ": ");
		error = ft_strjoin(error, strerror(errno));
		ft_putstr_fd(error, STDERR_FILENO);
		free(error);
	}
	else
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (0);
}

int	error_exit(char *str, t_shell *shell)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (errno)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	else
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit (shell->exit_status);
}

int	error_cmd(char *str)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd("Command not found: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit (127);
}

int	error_var(char *str, t_shell *shell)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd("Command not found: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	shell->exit_status = 127;
	return (0);
}

int	error_export(char *str, t_shell *shell)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	shell->exit_status = 1;
	return (0);
}
