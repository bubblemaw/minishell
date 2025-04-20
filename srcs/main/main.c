/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:34:48 by david             #+#    #+#             */
/*   Updated: 2025/04/20 18:22:26 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_exit_status = 0;

int	main(int ac, char *av[], char **env)
{
	t_shell	shell;

	ft_memset(&shell, 0, sizeof(t_shell));
	shell.env = copy_env(env);
	lvl_shell(&shell);
	init_execution(&shell);
	init_shell(&shell);
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, SIG_IGN);
	shell.export = NULL;
	save_pwd(&shell);
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
		if (shell.creat.err != NULL)
			free(shell.creat.err);
		init_shell(&shell);
		shell.input = readline("minishell$ ");
		if (shell.input == NULL)
			ft_exit_void(0, &shell);
		add_history(shell.input);
		if (enter_input(&shell) == VALID)
			continue ;
		else if (creat_tokken(shell.input, &shell) == ERROR)
		{
			g_exit_status = 2;
			ft_putstr_fd("syntax error near unexpected token\n", STDERR_FILENO);
			continue ;
		}
		if (give_token_data(&shell) == ERROR)
		{
			error_var(shell.creat.err);
			continue ;
		}
		check_here_doc_expansion(shell.tokken, &shell);
		// print_token(shell.tokken);
		ft_expansion(&shell);
		kill_quotes_new(&shell);
		init_execution(&shell);
		if (create_cmd_lst(&shell) == ERROR)
		{
			free_shell(&shell);
			error("loading commands");
		}
		if (export_boucle(&shell) == 0)
			init_var_local(&shell);
		// print_cmds(&shell.cmd);
		signal(SIGINT, signalhandler_exec);
		signal(SIGQUIT, signalhandler_back);
		ft_execute(&shell);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signalhandler);
	}
	return (0);
}
