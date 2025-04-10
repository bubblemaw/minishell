/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:20:25 by masase            #+#    #+#             */
/*   Updated: 2025/04/10 15:02:38 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipex_loop(t_cmd *current, t_shell *shell)
{
	while (current)
	{
		if (piper(current, shell) == CHILD_PROCESS)
		{
			ft_exe_pipe(current, shell);
		}
		else // PARENT PROCESS
		{
			// if (shell->invalid_redir == 1)
			// {
			// 	while (current && current->type != PIPE)
			// 		current = current->next;
			// 	shell->invalid_redir = 0;
			// }
			current = current->next;
		}
	}
}

int	child_processor(t_cmd *cmd , t_shell *shell, int *pipefd) //gestion entree sortie du child process avant son execution
{
	// char error_flag;

	// error_flag = 0;
	if (shell->prev_pipefd != -1) // reprendre l'entrée du pipe précédent
	{
		dup2(shell->prev_pipefd, STDIN_FILENO);
		close(shell->prev_pipefd);
	}
	if (cmd->infile) // si la commande recoit l'entrée d'un fichier infile
		if (ft_direction(cmd) == 0)
		{
			// error_flag = 1;
			// write(pipefd[1], &error_flag, sizeof(char));
			close (pipefd[1]);
			close(pipefd[0]);
			if (shell->prev_pipefd != -1)
				close (shell->prev_pipefd);
			exit(EXIT_FAILURE);
		}

	if (cmd->outfile) // si dernière commande -> redirection vers outfile ou terminal
	{
		if (ft_direction(cmd) == 0)
		{
			// error_flag = 1;
			// write(pipefd[1], &error_flag, sizeof(char));			
			close (pipefd[1]);
			close(pipefd[0]);
			if (shell->prev_pipefd != -1)
				close (shell->prev_pipefd);
			exit(EXIT_FAILURE);
		}
	}
	else if (cmd->next == NULL)
		dup2(shell->STDOUT, STDOUT_FILENO);
	else // sinon redirection vers pipe
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close (pipefd[1]);
	}
	// write(pipefd[1], &error_flag, sizeof(char));
	return (CHILD_PROCESS);
}

int	piper(t_cmd *cmd, t_shell *shell) // creation du pipe et fork
{
	int		pipefd[2];
	// char	error_flag;
	pid_t	pid;

		if (pipe(pipefd) == -1)
			return (error("error occurs during the pipe"));
		pid = fork();
		if (pid == -1)
			return (error("error occurs during the fork"));
		if (pid == 0)
			return(child_processor(cmd ,shell, pipefd));
		else
		{
			// if (read(pipefd[0], &error_flag, sizeof(char) > 0))
			// {
			// 	if (error_flag == 1)
			// 	{
			// 		shell->invalid_redir = 1;
			// 	}
			// }
			if (shell->prev_pipefd != -1) // fermeture du pipe de lecture dans le parent(pas besoin)
				close(shell->prev_pipefd);
			close(pipefd[1]);
			shell->prev_pipefd = pipefd[0];// sauvegarde du pipe de lecture pour la prochaine commande
			return (PARENT_PROCESS); // 
		}
}

int	ft_exe_pipe(t_cmd *cmd, t_shell *shell)// execution des fonctions qui precedé ou suivi d'un pipe
{
	char	*cmd_path;

	if (built_in_pipe(cmd, shell) == VALID)
		return (VALID);
	cmd_path = ft_parse(cmd, shell);
	if (cmd_path == NULL)
		return(error_cmd(cmd->arg[0]));
	if(execve(cmd_path, cmd->arg, shell->env) == -1)
		return(error_exit("execve failed"));
	return (VALID);
}