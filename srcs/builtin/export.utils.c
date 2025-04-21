/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:55:55 by masase            #+#    #+#             */
/*   Updated: 2025/04/21 11:34:00 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	display_export_env(t_shell *shell)
{
	// int	i;

	// i = 0;
	bubble_sort(shell->env, shell->export);
	// while (shell->env[i])
	// {
	// 	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	// 	write_until_char(shell->env[i], '=');
	// 	ft_putchar_fd('"', STDOUT_FILENO);
	// 	write_after_char(shell->env[i], '=');
	// 	ft_putchar_fd('"', STDOUT_FILENO);
	// 	ft_putchar_fd('\n', STDOUT_FILENO);
	// 	i++;
	// }
	// i = 0;
	// if (shell->export != NULL)
	// {
	// 	if (shell->export[i])
	// 	{
	// 		while (shell->export[i])
	// 		{
	// 			ft_putstr_fd("declare -x ", STDOUT_FILENO);
	// 			ft_putstr_fd(shell->export[i], STDOUT_FILENO);
	// 			ft_putchar_fd('\n', STDOUT_FILENO);
	// 			i++;
	// 		}
	// 	}
	// }
	return (VALID);
}

int	write_until_char(char *str, char c)
{
	int	i;
	int result;

	i = 0;
	result = ERROR;
	while (str[i] != '\0')
	{
		write(STDOUT_FILENO, &str[i], 1);
		if (str[i] == c)
		{
			result = VALID;
			break ;
		}
		i++;
	}
	return (result);
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

void add_export(t_shell *shell, t_token *tmp)
{
    int i;
    char **new_export;
    char *new_value;

    if (!tmp || !tmp->value)
        return;
    new_value = ft_strdup(tmp->value);
    if (!new_value)
        return;
    if (shell->export == NULL)
    {
        shell->export = malloc(sizeof(char *) * 2);
        if (!shell->export)
        {
            free(new_value);
            return;
        }
        shell->export[0] = new_value;
        shell->export[1] = NULL;
        return;
    }
    i = 0;
    while (shell->export[i] != NULL)
        i++;
    new_export = malloc(sizeof(char *) * (i + 2)); // i existing + new + NULL
    if (!new_export)
    {
        free(new_value);
        return;
    }
    for (int j = 0; j < i; j++)
        new_export[j] = shell->export[j];
    new_export[i] = new_value;
    new_export[i + 1] = NULL;
    free(shell->export);
    shell->export = new_export;
}
