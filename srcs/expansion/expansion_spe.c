/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_spe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:14:55 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/23 09:21:09 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	special_cases(t_shell *shell, char *current, int *i)
{
	if (error_case(shell, current, i) == VALID)
		return (VALID);
	if (pid_dolls(shell, current, i) == VALID)
		return (VALID);
	if (wave(shell, current, i) == VALID)
		return (VALID);
	return (0);
}

int	error_case(t_shell *shell, char *current, int *i)
{
	if (current[1] == '?')
	{
		if (shell->exp.new == NULL)
		{
			shell->exp.tmp_2 = ft_itoa(shell->exit_status);
			shell->exp.new = ft_strdup(shell->exp.tmp_2);
			free(shell->exp.tmp_2);
		}
		else
		{
			shell->exp.tmp_2 = shell->exp.new;
			shell->exp.tmp_3 = ft_itoa(shell->exit_status);
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

int	pid_dolls(t_shell *shell, char *current, int *i)
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

int	wave(t_shell *shell, char *current, int *i)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = NULL;
	if (current[0] == '~'
		&& (current[1] == ' ' || current[1] == '\0'
			|| current[1] == '/'))
	{
		while (shell->env[j] != NULL)
		{
			tmp = ft_substr(shell->env[j], 0, 4);
			switch_home(tmp, shell, &j);
			free(tmp);
			j++;
		}
		(*i)++;
		shell->exp.start = *i;
		return (VALID);
	}
	return (0);
}

void	switch_home(char *tmp, t_shell *shell, int *j)
{
	if (ft_strncmp(tmp, "HOME", 4) == 0)
	{
		if (shell->exp.new == NULL)
			shell->exp.new = ft_strdup(shell->env[*j] + 5);
		else
		{
			shell->exp.tmp = shell->exp.new;
			shell->exp.new = ft_strjoin(shell->exp.new, shell->env[*j] + 5);
			free(shell->exp.tmp);
		}
	}
	return ;
}
