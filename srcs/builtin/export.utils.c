/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:55:55 by masase            #+#    #+#             */
/*   Updated: 2025/04/20 21:51:39 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	display_export_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		write_until_char(shell->env[i], '=');
		ft_putchar_fd('"', STDOUT_FILENO);
		write_after_char(shell->env[i], '=');
		ft_putchar_fd('"', STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	i = 0;
	if (shell->export != NULL)
	{
		if (shell->export[i])
		{
			while (shell->export[i])
			{
				ft_putstr_fd("declare -x ", STDOUT_FILENO);
				ft_putstr_fd(shell->export[i], STDOUT_FILENO);
				ft_putchar_fd('\n', STDOUT_FILENO);
				i++;
			}
		}
	}
	return (VALID);
}

void	write_until_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(STDOUT_FILENO, &str[i], 1);
		if (str[i] == c)
			break ;
		i++;
	}
	return ;
}

void	write_after_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	i++;
	while (str[i] != '\0')
	{
		write(STDOUT_FILENO, &str[i], 1);
		i++;
	}
	return ;
}

void	add_export(t_shell *shell, t_token *tmp)
{
	int	i;

	i = 0;
	if (shell->export == NULL)
	{
		shell->export = malloc(sizeof(char *) * 2);
		if (shell->export == NULL)
			return ;
		shell->export[0] = ft_strdup(tmp->value);
		shell->export[1] = NULL;
		return ;
	}
	while (shell->export[i] != NULL)
		i++;
	shell->export = ft_realloc(shell->export, i * sizeof(char *),
			(i + 1) * sizeof(char *));
	if (shell->export == NULL)
		return ;
	shell->export[i] = ft_strdup(tmp->value);
	shell->export[i + 1] = NULL;
}


