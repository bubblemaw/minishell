/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 22:02:06 by david             #+#    #+#             */
/*   Updated: 2025/04/21 12:28:09 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	calculate_size(char **tab)
{
	int	size;

	size = 0;
	if (tab != NULL)
	{
		while (tab[size] != NULL)
			size++;
	}
	return (size);
}

void	print_and_free(char **temp, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (write_until_char(temp[i], '=') == VALID)
		{
			ft_putchar_fd('"', STDOUT_FILENO);
			write_after_char(temp[i], '=');
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		free(temp[i]);
		i++;
	}
	free(temp);
}
