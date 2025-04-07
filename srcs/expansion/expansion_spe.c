/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_spe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:14:55 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/07 18:22:21 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	error_case(t_shell  *shell, char *current)
{
	char	*tmp;
	char	*tmp_2;

	tmp = NULL;
	tmp_2 = NULL;
	if (current[1] == '?')
	{
		if (shell->exp.new == NULL)
		{
			tmp = ft_itoa(g_exit_status);
			shell->exp.new = ft_strdup(tmp);
			free(tmp);
		}
		else
		{
			tmp = shell->exp.new;
			tmp_2 = ft_itoa(g_exit_status);
			shell->exp.new = ft_strjoin(shell->exp.new, tmp_2);
			free(tmp);
			free(tmp_2);
		}
		return (VALID);
	}
	return (0);
} 

int	pid_dolls(t_shell  *shell, char *current)
{
	int		fd;

	if (current[1] == '$')
	{
		fd = open("/proc/self/stat", O_RDONLY);
		if (fd == -1)
			return (0);
		shell->exp.line = get_next_line(fd);
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
		return (VALID);
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
