/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:55:55 by masase            #+#    #+#             */
/*   Updated: 2025/04/21 12:13:05 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	write_until_char(char *str, char c)
{
	int	i;
	int	result;

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

void	add_export(t_shell *shell, t_token *tmp)
{
	int		i;
	char	**new_export;
	char	*new_value;

	new_value = ft_strdup(tmp->value);
	if (if_tab_is_empty(shell, new_value) == VALID)
		return ;
	i = 0;
	while (shell->export[i] != NULL)
		i++;
	new_export = malloc(sizeof(char *) * (i + 2));
	if (!new_export)
	{
		free(new_value);
		return ;
	}
	copy_export_tab(shell, new_export, i);
	new_export[i] = new_value;
	new_export[i + 1] = NULL;
	free(shell->export);
	shell->export = new_export;
}

void	copy_export_tab(t_shell *shell, char **new_export, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		new_export[j] = shell->export[j];
		j++;
	}
}

int	if_tab_is_empty(t_shell *shell, char *new_value)
{
	if (shell->export == NULL)
	{
		shell->export = malloc(sizeof(char *) * 2);
		if (!shell->export)
		{
			free(new_value);
			return (0);
		}
		shell->export[0] = new_value;
		shell->export[1] = NULL;
		return (VALID);
	}
	return (0);
}
