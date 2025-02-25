/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:16:38 by maw               #+#    #+#             */
/*   Updated: 2025/02/25 16:43:57 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_execute(t_token *token, t_shell *shell)
{
	while (token)
	{
		if (token->infile || token->outfile) // redirection infile outfile
			ft_direction(token);
		if (token->delimiter)
			here_doc(token, shell);
		if (token->type == PIPE) // si il ya des operations avec des pipes
		{
			while (token)
			{
				if (piper(token, shell) == CHILD_PROCESS)
					ft_exe_pipe(token);
				else // PARENT PROCESS
					token = token->next;
			}
		}
		else // execution commande basique
		{
			// gérer cas fonctions builtin
			ft_exe(token);
			token = token->next;
		}
		// if (token->delimiter)
		// 	unlink("here_doc");
	}
	while (wait(NULL) > 0); // attente de tous les childs process 
	reset_fd(shell);
	ft_printf("on a fini toutes les commande\n");
	return (1);
}

int child_processor(t_shell *shell, t_token *cmd, int *pipefd) //gestion entree sortie du child process avant son execution
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

int piper(t_token *cmd, t_shell *shell) // creation du pipe et fork
{
	int pipefd[2];
	pid_t pid;
	
		if (pipe(pipefd) == -1)
			return (error("error occurs during the pipe"));
		pid = fork();
		if (pid == -1)
			return (error("error occurs during the fork"));
		if (pid == 0)
			return(child_processor(shell, cmd, pipefd));
		else
		{
			if (shell->prev_pipefd != -1) // fermeture du pipe de lecture dans le parent(pas besoin)
				close(shell->prev_pipefd);
			close(pipefd[1]);
			shell->prev_pipefd = pipefd[0];// sauvegarde du pipe de lecture pour la prochaine commande
			return (PARENT_PROCESS); // 
		}
}

int ft_exe_pipe(t_token *token)// execution des fonctions qui precedé ou suivi d'un pipe
{
	char *cmd_path;

	cmd_path = ft_parse(token);
	if(execve(cmd_path, token->arg, NULL) == -1)
		return(error("Execution problem"));
	return (1);
}

int ft_exe(t_token *token) // execution des commandes normales (sans pipe)
{
	pid_t pid1;
	char *cmd_path;
	int status;

	status = 0;
	pid1 = fork();
	if (pid1 == 0)
	{
		cmd_path = ft_parse(token);
		if (cmd_path == NULL)
			return(error("Command not found"));
		if(execve(cmd_path, token->arg, NULL) == -1)
			return(error("Execution problem"));
	}
	else
		waitpid(pid1, &status, 0);
	return (1);
}

int main(int ac, char **av, char **env)
{
	t_token *token_list = NULL;
	t_shell shell;

	init_execution(&shell);

	// Simulation de commandes
	char **cmd1 = malloc(3 * sizeof(char *));
	cmd1[0] = strdup("cat");
	// cmd1[1] = strdup("a");
	cmd1[1] = NULL;

	// char **cmd2 = malloc(3 * sizeof(char *));
	// cmd2[0] = strdup("cat");
	// // cmd2[1] = strdup("txt");
	// cmd2[1] = NULL;

	// char **cmd3 = malloc(3 * sizeof(char *));
	// cmd3[0] = strdup("sort");
	// // cmd3[1] = strdup("13");
	// cmd3[1] = NULL;

	// Ajout des commandes à la liste
	add_cmd(&token_list, cmd1, NULL, "outfile20", "EOF", 1, 0);   // ls -l > output.txt
	// add_cmd(&token_list, cmd2, NULL, "outfile9", 0, 0); // grep main < output.txt >> final.txt
	// add_cmd(&token_list, cmd3, NULL, "outfile10", 0, 0);
	
	// execution de la liste de commande
	ft_execute(token_list, &shell);

	// Libération de la mémoire
	free_cmds(token_list);
	return 0;
}
