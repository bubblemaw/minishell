/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_spe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:14:55 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/06 21:47:33 by david            ###   ########.fr       */
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
		if (shell->utils.new_arg == NULL)
		{
			tmp = ft_itoa(g_exit_status);
			shell->utils.new_arg = ft_strdup(tmp);
			free(tmp);
		}
		else
		{
			tmp = shell->utils.new_arg;
			tmp_2 = ft_itoa(g_exit_status);
			shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, tmp_2);
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
	char	*line;
	char	**tab;
	char	*tmp;

	if (current[1] == '$')
	{
		fd = open("/proc/self/stat", O_RDONLY);
		if (fd == -1)
			return (0);
		line = get_next_line(fd);
		if (line == NULL)
			return (0);
		tab = ft_split(line, ' ');
		if (shell->utils.new_arg == NULL)
			shell->utils.new_arg = ft_strdup(tab[3]);
		else
		{
			tmp = shell->utils.new_arg;
			shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, tab[3]);	
		}
		free(tmp);
		free_split(tab);
		free(line);
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
