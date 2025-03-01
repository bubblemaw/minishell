/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:34:48 by david             #+#    #+#             */
/*   Updated: 2025/03/01 20:42:50 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main (void)
{
	t_shell shell;

	ft_memset(&shell, 0, sizeof(t_shell));
	// shell.creat.test = PIPE;
	// printf("result : %d\n", shell.creat.test);
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
			printf("Syntaxe Error...\n");
		printf("\n");
		print_token(shell.tokken);
		printf("\n");
	}
	return (0);
}
