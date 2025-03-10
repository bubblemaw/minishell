/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:00:12 by maw               #+#    #+#             */
/*   Updated: 2025/03/08 16:15:08 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void free_shell(t_shell *shell)
{
	if (shell->env)
		free_tab(shell->env);
	if (shell->cmd)
		free_cmds(&shell->cmd);
	// if (shell->tokken)
	// 	free_list(shell->tokken);
	// if (shell->input)
	// 	free(shell->input);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}
