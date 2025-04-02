/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_spe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:14:55 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/02 11:53:27 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	specials_case(t_shell  *shell, char *current)
{
	if (current[1] == '?')
	{
		if (shell->utils.new_arg == NULL)
			shell->utils.new_arg = ft_strdup(ft_itoa(g_exit_status));
		else
			shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, ft_itoa(g_exit_status));
		return (VALID);
	}
	return (0);
}

int	pid_dolls(t_shell  *shell, char *current)
{
	int		fd;
	char	*line;
	char	**tab;

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
			shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, tab[3]);
		return (VALID);
	}
	return (0);
}
