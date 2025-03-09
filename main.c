/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:34:48 by david             #+#    #+#             */
/*   Updated: 2025/03/09 18:00:44 by maw              ###   ########.fr       */
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
			print_cmds(shell.cmd);
			shell.cmd = NULL;
		}
		shell.input = readline("minishell$ ");
		if (strncmp(shell.input, "exit ", 4) == 0)
		{
			free_shell(&shell);
			free(shell.input); 
			return (0);
		}
		if (creat_tokken(shell.input, &shell) == ERROR)
		{
			printf("Syntaxe Error...\n");
			continue;
		}
		give_token_data(&shell);
		// printf("\n");
		// print_token(shell.tokken);
		// printf("\n");
		if (create_cmd_lst(&shell) == ERROR)
		{
			free_shell(&shell);
			error("Error loadind commands\n");
		}
		// print_cmds(shell.cmd);
		ft_execute(&shell);
	}
	return (0);
}
