/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:34:48 by david             #+#    #+#             */
/*   Updated: 2025/03/12 16:47:35 by masase           ###   ########.fr       */
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
			printf("je rentre pour free command\n");
			free_cmds(&shell.cmd);
			shell.cmd = NULL;
		}
		shell.input = readline("minishell$ ");
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
		// print_token(shell.tokken);
		// printf("\n");
		init_execution(&shell);
		if (create_cmd_lst(&shell) == ERROR)
		{
			free_shell(&shell);
			error("loadind commands\n");
		}
		printf("j'ai fini de cree la cmd liste\n");
		print_cmds(shell.cmd);
		ft_execute(&shell);
	}
	return (0);
}
