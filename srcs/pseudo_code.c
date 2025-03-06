/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:16:38 by maw               #+#    #+#             */
/*   Updated: 2025/03/06 17:19:03 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_execute(t_shell *shell)
{
	while (shell->cmd)
	{
		if (shell->cmd->infile || shell->cmd->outfile) // redirection infile outfile
			ft_direction(shell->cmd);
		if (shell->cmd->delimiter)
			here_doc(shell);
		if (shell->cmd->type == PIPE) // si il ya des operations avec des pipes
		{
			while (shell->cmd != NULL)
			{
				if (piper(shell) == CHILD_PROCESS)
					ft_exe_pipe(shell->cmd);
				else // PARENT PROCESS
					shell->cmd = shell->cmd->next;
			}
		}
		else // execution commande basique
		{
			// gérer cas fonctions builtin
			ft_exe(shell->cmd);
			shell->cmd = shell->cmd->next;
		}
	}
	while (wait(NULL) > 0); // attente de tous les childs process 
	reset_fd(shell);
	printf("on a fini toutes les commande\n");
	return (1);
}

int child_processor(t_shell *shell, int *pipefd) //gestion entree sortie du child process avant son execution
{
	if (shell->prev_pipefd != -1) // reprendre l'entrée du pipe précédent
	{
		dup2(shell->prev_pipefd, STDIN_FILENO);
		close(shell->prev_pipefd);
	}
	if (shell->cmd->infile) // si la commande recoit l'entrée d'un fichier infile
		ft_direction(shell->cmd);
	if (shell->cmd->next == NULL) // si dernière commande -> redirection vers outfile ou terminal
	{
		if (shell->cmd->outfile)
			ft_direction(shell->cmd);
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

int piper(t_shell *shell) // creation du pipe et fork
{
	int pipefd[2];
	pid_t pid;
	
		if (pipe(pipefd) == -1)
			return (error("error occurs during the pipe"));
		pid = fork();
		if (pid == -1)
			return (error("error occurs during the fork"));
		if (pid == 0)
			return(child_processor(shell, pipefd));
		else
		{
			if (shell->prev_pipefd != -1) // fermeture du pipe de lecture dans le parent(pas besoin)
				close(shell->prev_pipefd);
			close(pipefd[1]);
			shell->prev_pipefd = pipefd[0];// sauvegarde du pipe de lecture pour la prochaine commande
			return (PARENT_PROCESS); // 
		}
}

int ft_exe_pipe(t_cmd *cmd)// execution des fonctions qui precedé ou suivi d'un pipe
{
	char *cmd_path;

	cmd_path = ft_parse(cmd);
	if(execve(cmd_path, cmd->arg, NULL) == -1)
		return(error("Execution problem"));
	return (1);
}

int ft_exe(t_cmd *cmd) // execution des commandes normales (sans pipe)
{
	pid_t pid1;
	char *cmd_path;
	int status;

	status = 0;
	pid1 = fork();
	if (pid1 == 0)
	{
		if (built_in(cmd) == 1)
			return (1);
		cmd_path = ft_parse(cmd);
		if (cmd_path == NULL)
			return(error("Command not found"));
		if(execve(cmd_path, cmd->arg, NULL) == -1)
			return(error("Execution problem"));
	}
	else
		waitpid(pid1, &status, 0);
	return (1);
}

// int main(int ac, char **av, char **env)
// {
// 	t_shell shell;

// 	init_execution(&shell, env);

// 	// Simulation de commandes
// 	char **cmd1 = malloc(3 * sizeof(char *));
// 	cmd1[0] = strdup("ls");
// 	cmd1[1] = strdup("-la");
// 	// cmd1[2] = strdup("you have to be confident");
// 	// cmd1[3] = strdup("for real");
// 	// cmd1[4] = strdup("$VAR");
// 	cmd1[2] = NULL;

// 	char **cmd2 = malloc(3 * sizeof(char *));
// 	cmd2[0] = strdup("cat");
// 	// cmd2[1] = strdup("txt");
// 	cmd2[1] = NULL;

// 	// char **cmd3 = malloc(3 * sizeof(char *));
// 	// cmd3[0] = strdup("sort");
// 	// // cmd3[1] = strdup("13");
// 	// cmd3[1] = NULL;

// 	// Ajout des commandes à la liste
// 	add_cmd(&shell.cmd, cmd1, NULL, NULL, NULL, 0, PIPE);   // ls -l > output.txt
// 	add_cmd(&shell.cmd, cmd2, NULL, NULL, NULL, 0, 0); // grep main < output.txt >> final.txt
// 	// add_cmd(&token_list, cmd3, NULL, "outfile10", 0, 0);
	
// 	// execution de la liste de commande
// 	// expansion(&token_list, &shell);
// 	ft_execute(&shell);

// 	// Libération de la mémoire
// 	free_cmds(shell.cmd);
// 	return 0;
// }
