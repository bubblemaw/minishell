/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:34:48 by david             #+#    #+#             */
/*   Updated: 2025/04/23 10:10:02 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_main(t_shell *shell, char **env)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->env = copy_env(env);
	lvl_shell(shell);
	init_execution(shell);
	init_shell(shell);
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, SIG_IGN);
	shell->export = NULL;
	save_pwd(shell);
}

void	free_before_prompt(t_shell *shell)
{
	if (shell->tokken != NULL || shell->input)
	{
		free(shell->input);
		free_list(shell->tokken);
		shell->tokken = NULL;
	}
	if (shell->cmd != NULL)
	{
		free_cmds(&shell->cmd);
		shell->cmd = NULL;
	}
	if (shell->creat.err != NULL)
		free(shell->creat.err);
	init_shell(shell);
}

void	start_execution(t_shell *shell)
{
	check_here_doc_expansion(shell->tokken, shell);
	ft_expansion(shell);
	kill_quotes_new(shell);
	init_execution(shell);
	if (create_cmd_lst(shell) == ERROR)
	{
		free_shell(shell);
		error("loading commands");
	}
	if (export_boucle(shell) == 0)
		init_var_local(shell);
	signal(SIGINT, signalhandler_exec);
	ft_execute(shell);
	signal(SIGINT, signalhandler);
}

void	read_input(t_shell *shell)
{
	shell->input = readline("minishell$ ");
	if (shell->input == NULL)
		ft_exit_void(0, shell);
	add_history(shell->input);
}

int	main(int ac, char *av[], char **env)
{
	t_shell	shell;

	(void)av;
	(void)ac;
	init_main(&shell, env);
	while (1)
	{
		free_before_prompt(&shell);
		read_input(&shell);
		if (enter_input(&shell) == VALID)
			continue ;
		else if (creat_tokken(shell.input, &shell) == ERROR)
		{
			shell.exit_status = 2;
			ft_putstr_fd("syntax error near unexpected token\n", STDERR_FILENO);
			continue ;
		}
		if (give_token_data(&shell) == ERROR)
		{
			error_var(shell.creat.err, &shell);
			continue ;
		}
		start_execution(&shell);
	}
	return (0);
}
