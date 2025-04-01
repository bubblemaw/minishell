/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:16:38 by maw               #+#    #+#             */
/*   Updated: 2025/03/31 17:27:31 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_execute(t_shell *shell)
{
	t_cmd *current;
	
	current = shell->cmd;
	while (current)
	{
		if (current->infile || current->outfile) // redirection infile outfile
			if (ft_direction(current) == 0)
				return (ERROR);
		if (current->delimiter)
			here_doc(current ,shell);
		if (current->type == PIPE) // si il ya des operations avec des pipes
		{
			pipex_loop(current, shell);
				break ;
		}
		else // execution commande basique
			ft_exe(current, shell);
		current = current->next;
	}
	while (wait(&g_exit_status) > 0); // attente de tous les childs process 
	printf("apres waitall%d\n", g_exit_status);
	reset_fd(shell);
	return (VALID);
}

void pipex_loop(t_cmd *current, t_shell *shell)
{
	while (current)
	{
		if (piper(current, shell) == CHILD_PROCESS)
			ft_exe_pipe(current, shell);
		else // PARENT PROCESS
			current = current->next;
	}
}

int child_processor(t_cmd *cmd , t_shell *shell, int *pipefd) //gestion entree sortie du child process avant son execution
{
	if (shell->prev_pipefd != -1) // reprendre l'entrée du pipe précédent
	{
		dup2(shell->prev_pipefd, STDIN_FILENO);
		close(shell->prev_pipefd);
	}
	if (cmd->infile) // si la commande recoit l'entrée d'un fichier infile
		ft_direction(cmd);
	if (cmd->next == NULL) // si dernière commande -> redirection vers outfile ou terminal
	{
		if (cmd->outfile)
			ft_direction(cmd);
		else
			dup2(shell->STDOUT, STDOUT_FILENO);
		return (CHILD_PROCESS); 
	}
	else // sinon redirection vers pipe
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close (pipefd[1]);
		return (CHILD_PROCESS);
	}
}

int piper(t_cmd *cmd, t_shell *shell) // creation du pipe et fork
{
	int pipefd[2];
	pid_t pid;

		if (pipe(pipefd) == -1)
			return (error("error occurs during the pipe"));
		pid = fork();
		if (pid == -1)
			return (error("error occurs during the fork"));
		if (pid == 0)
			return(child_processor(cmd ,shell, pipefd));
		else
		{
			if (shell->prev_pipefd != -1) // fermeture du pipe de lecture dans le parent(pas besoin)
				close(shell->prev_pipefd);
			close(pipefd[1]);
			shell->prev_pipefd = pipefd[0];// sauvegarde du pipe de lecture pour la prochaine commande
			return (PARENT_PROCESS); // 
		}
}

int ft_exe_pipe(t_cmd *cmd, t_shell *shell)// execution des fonctions qui precedé ou suivi d'un pipe
{
	char *cmd_path;

	cmd_path = ft_parse(cmd, shell);
	if (cmd_path == NULL)
		return(error_cmd(cmd->arg[0]));
	if(execve(cmd_path, cmd->arg, shell->env) == -1)
		return(error_exit("execve failed"));
	return (VALID);
}

int ft_exe(t_cmd *cmd, t_shell *shell) // execution des commandes normales (sans pipe)
{
	pid_t pid1;
	char *cmd_path;

	if (cmd->arg == NULL)
		return(ERROR);
	if (built_in(cmd, shell) == VALID)
		return (VALID);
	pid1 = fork();
	if (pid1 == 0)
	{
		cmd_path = ft_parse(cmd, shell);
		if (cmd_path == NULL)
			return(error_cmd(cmd->arg[0]));
		if(execve(cmd_path, cmd->arg, shell->env) == -1)
			return(error_exit("execve failed"));
	}
	else
	{
		waitpid(pid1, &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
		{
			g_exit_status = WEXITSTATUS(g_exit_status);
		}
	}
	return (VALID);
}

