/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:34:48 by david             #+#    #+#             */
/*   Updated: 2025/03/10 00:16:26 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main (int ac, char *av[], char **env)
{
	t_shell shell;

	ft_memset(&shell, 0, sizeof(t_shell));
	init_execution(&shell, env);
	(void)av;
	(void)ac;
	
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
		if (enter_input(&shell) == VALID)
			continue;
		if (strncmp(shell.input, "exit ", 4) == 0)
		{
			free(shell.input); 
			return (0);
		}
		if (creat_tokken(shell.input, &shell) == ERROR)
		{
			printf("Syntaxe Error...\n");
			continue;
		}
		give_token_data(&shell);
		printf("\n");
		print_token(shell.tokken);
		printf("\n");
		// create_cmd_lst(&shell);
		// print_cmds(shell.cmd);
		// ft_execute(&shell);
	}
	return (0);
}
