/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_spe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:14:55 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/08 11:05:42 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	error_case(t_shell  *shell, char *current, int *i)
{
	if (current[1] == '?')
	{
		if (shell->exp.new == NULL)
		{
			shell->exp.tmp_2 = ft_itoa(g_exit_status);
			shell->exp.new = ft_strdup(shell->exp.tmp_2);
			free(shell->exp.tmp_2);
		}
		else
		{
			shell->exp.tmp_2 = shell->exp.new;
			shell->exp.tmp_3 = ft_itoa(g_exit_status);
			shell->exp.new = ft_strjoin(shell->exp.new, shell->exp.tmp_3);
			free(shell->exp.tmp_2);
			free(shell->exp.tmp_3);
		}
		*i += 2;
		shell->exp.start = *i;
		return (VALID);
	}
	return (0);
} 

int	pid_dolls(t_shell  *shell, char *current, int *i)
{
	if (current[1] == '$')
	{
		shell->exp.fd = open("/proc/self/stat", O_RDONLY);
		if (shell->exp.fd == -1)
			return (0);
		shell->exp.line = get_next_line(shell->exp.fd);
		if (shell->exp.line == NULL)
			return (0);
		shell->exp.tab = ft_split(shell->exp.line, ' ');
		if (shell->exp.new == NULL)
			shell->exp.new = ft_strdup(shell->exp.tab[3]);
		else
		{
			shell->exp.temp = shell->exp.new;
			shell->exp.new = ft_strjoin(shell->exp.new, shell->exp.tab[3]);	
		}
		free(shell->exp.temp);
		free_split(shell->exp.tab);
		free(shell->exp.line);
		*i += 2;
		shell->exp.start = *i;
		return (VALID);
	}
	return (0);
}

int only_dolls(t_shell *shell, t_token *current, int *i)
{
	shell->exp.size_var = var_size(current->value + *i);
	if (shell->exp.size_var == 0)
	{
		shell->exp.tmp = shell->exp.new;
		shell->exp.new = ft_strjoin(shell->exp.new, "$");
		free(shell->exp.tmp);
	}
	return (0);
}

int	result(t_shell *shell, t_token *current, int *i)
{
	if (current->value[*i] == '\0' && shell->exp.new == NULL)
		return (0);
	else if (current->value[shell->exp.start] != '\0')
	{
		shell->exp.tmp = shell->exp.new;
		shell->exp.new = ft_strjoin(shell->exp.new, current->value + shell->exp.start);
		free(shell->exp.tmp);
	}
	if (shell->exp.new)
	{
		free(current->value);
		current->value = ft_strdup(shell->exp.new);
		free(shell->exp.new);
		shell->exp.new = NULL;
	}
	return (0);
}

void	free_split(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return ;
}
