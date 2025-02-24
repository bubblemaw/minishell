/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:34:48 by david             #+#    #+#             */
/*   Updated: 2025/02/24 17:25:04 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main (void)
{
	t_shell shell;

	ft_memset(&shell, 0, sizeof(t_shell));
	while (1)
	{
		if (shell.tokken != NULL)
		{
			free_list(shell.tokken);
			shell.tokken = NULL;
		}
		shell.input = readline("minishell$ ");
		if (strncmp(shell.input, "exit ", 4) == 0)
		{
			free(shell.input); 
			return (0);
		}
		if (creat_tokken(shell.input, &shell) == ERROR)
			printf("Error command not found\n");
	}
	return (0);
}
