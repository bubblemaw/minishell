/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:34:48 by david             #+#    #+#             */
/*   Updated: 2025/03/16 18:57:53 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main (int ac, char *av[], char **env)
{
	t_shell shell;

	ft_memset(&shell, 0, sizeof(t_shell));
	shell.env = copy_env(env);
	init_execution(&shell);
	(void)av;
	(void)ac;

	while (1)
	{
		if (shell.tokken != NULL)
		{
			free_list(shell.tokken);
			shell.tokken = NULL;
		}
		if (shell.cmd != NULL)
		{
			free_cmds(&shell.cmd);
			shell.cmd = NULL;
		}
		shell.input = readline("minishell$ ");
		add_history(shell.input);
		if (enter_input(&shell) == VALID)
			continue ;
		else if (strncmp(shell.input, "exit ", 4) == 0)
		{
			free_shell(&shell);
			free(shell.input); 
			return (0);
		}
		else if (creat_tokken(shell.input, &shell) == ERROR)
		{
			printf("Syntaxe Error...\n");
			continue ;
		}
		give_token_data(&shell);
		// printf("\n");
		// print_token(shell.tokken);s
		// printf("\n");
		init_execution(&shell);
		if (create_cmd_lst(&shell) == ERROR)
		{
			free_shell(&shell);
			error("loading commands\n");
		}
		// print_cmds(shell.cmd);
		ft_execute(&shell);
		// printf("execution fini\n");
	}
	return (0);
}
