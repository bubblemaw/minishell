/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:34:48 by david             #+#    #+#             */
/*   Updated: 2025/04/07 13:42:38 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_exit_status = 0;

int	main (int ac, char *av[], char **env)
{
	t_shell	shell;

	ft_memset(&shell, 0, sizeof(t_shell));
	shell.env = copy_env(env);
	init_execution(&shell);
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, SIG_IGN);
	(void)av;
	(void)ac;

	while (1)
	{
		if (shell.tokken != NULL || shell.input)
		{
			free(shell.input);
			free_list(shell.tokken);
			shell.tokken = NULL;
		}
		if (shell.cmd != NULL)
		{
			free_cmds(&shell.cmd);
			shell.cmd = NULL;
		}
		shell.input = readline("minishell$ ");
		if (shell.input == NULL)
			ft_exit_void(0, &shell);
		add_history(shell.input);
		if (enter_input(&shell) == VALID)
			continue ;
		else if (creat_tokken(shell.input, &shell) == ERROR)
		{
			printf("Syntaxe Error...\n");
			continue ;
		}
		give_token_data(&shell);
		ft_expansion(&shell);
		kill_quotes(&shell);
		init_execution(&shell);
		if (create_cmd_lst(&shell) == ERROR)
		{
			free_shell(&shell);
			error("loading commands\n");
		}
		init_var_local(&shell);
		ft_execute(&shell);
	}
	return (0);
}
