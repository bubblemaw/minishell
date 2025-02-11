/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:02:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/02/11 15:39:57 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int gestion_tokken_1(char *input)
// {
// 	return (0);
// }

int	main (void)
{
	char *input;

	while (1)
	{
		input = readline("minishell$ ");
		if (strncmp(input, "exit ", 4) == 0)
		{
			free(input);
			return (0);
		}
	}
	return (0);
}
