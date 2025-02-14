/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:16:38 by maw               #+#    #+#             */
/*   Updated: 2025/02/14 17:03:24 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// int execution(t_cmd *cmd)
// {
//     int pipefd[2];
//     int pids[50];
//     int i = 0;
//     int prev_pipe_read = -1; // Descripteur de lecture du pipe précédent

//     while (cmd)
//     {
//         // Créer un nouveau pipe si la commande est suivie d'un pipe
//         if (cmd->type == 1)
//         {
//             if (pipe(pipefd) == -1)
//             {
//                 ft_putstr_fd("erreur de pipe\n", 2);
//                 return (-1);
//             }
//         }

//         // Exécuter la commande
//         pids[i] = execute_cmd(cmd, prev_pipe_read, (cmd->type == 1) ? pipefd[1] : -1);

//         // Fermer le descripteur de lecture du pipe précédent
//         if (prev_pipe_read != -1)
//             close(prev_pipe_read);

//         // Mettre à jour prev_pipe_read pour la prochaine commande
//         if (cmd->type == 1)
//         {
//             prev_pipe_read = pipefd[0]; // L'extrémité de lecture du pipe actuel
//             close(pipefd[1]); // Fermer l'extrémité d'écriture du pipe actuel
//         }
//         else
//         {
//             prev_pipe_read = -1; // Pas de pipe après cette commande
//         }

//         // Passer à la commande suivante
//         cmd = cmd->next;
//         i++;
//     }

//     // Attendre que tous les processus enfants se terminent
//     int j = 0;
//     while (j < i)
//     {
//         waitpid(pids[j], NULL, 0);
//         j++;
//     }

//     return (1);
// }

int execute_cmd(t_cmd *cmd, int input_fd, int output_fd)
{
    char *cmd_path;
    int infd;
    int outfd;
    pid_t pid;

    pid = fork();
    if (pid == 0) // Processus enfant
    {
        // Rediriger l'entrée standard (stdin)
        if (input_fd != -1)
        {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        // Rediriger la sortie standard (stdout)
        if (output_fd != -1)
        {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        // Redirection depuis un fichier d'entrée
        if (cmd->infile)
        {
            infd = open(cmd->infile, O_RDONLY);
            if (infd == -1)
                ft_putstr_fd("erreur open du fichier\n", 2);
            dup2(infd, STDIN_FILENO);
            close(infd);
        }

        // Redirection vers un fichier de sortie
        if (cmd->outfile)
        {
            outfd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (outfd == -1)
                ft_putstr_fd("erreur open du fichier\n", 2);
            dup2(outfd, STDOUT_FILENO);
            close(outfd);
        }

        // Exécuter la commande
        cmd_path = ft_parse(cmd);
        if (execve(cmd_path, cmd->arg, NULL) == -1)
        {
            ft_putstr_fd("probleme d'execution\n", 2);
            exit(1);
        }
    }
    else if (pid < 0) // Erreur de fork
    {
        ft_putstr_fd("erreur de fork\n", 2);
        return (-1);
    }

    return (pid);
}



int execution(t_cmd *cmd)
{
    int     leftfd[2];
    int     rightfd[2];
	int		pids[50];
	int		i;
	int		j;

    leftfd[0] = -1;
    leftfd[1] = -1;
	i = 0;
    ft_putstr_fd("ton pere\n", 1);
	while(cmd)
	{
        if (cmd->type == 1)
        {
            if (pipe(rightfd) == -1)
                ft_putstr_fd("erreur de pipe\n", 2);
        }
		pids[i] = execute_cmd(cmd, leftfd, rightfd);
		if (leftfd[0] != -1)
            close(leftfd[0]);
        if (leftfd[1] != -1)
            close(leftfd[1]);
        leftfd[0] = rightfd[0];
        leftfd[1] = rightfd[1];
		if (cmd->type != 1)
		{
			if (rightfd[0] != -1)
            	close(rightfd[0]);
        	if (rightfd[1] != -1)
            	close(rightfd[1]);
		}

		//iterate trough commands
		cmd = cmd->next;
		i++;
	}
	j = 0;
	while (j < i)
	{
		ft_putstr_fd("on attend\n", 1);
		waitpid(pids[j], NULL, 0);
		j++;
	}
	return (1);
}

int execute_cmd(t_cmd *cmd, int *leftfd, int *rightfd)
{
    char *cmd_path;
    int     infd;
    int     outfd;
	int stdin;
	int stdout;
    pid_t   pid1;
    int status;

    status = 0;
    cmd_path = NULL;
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	//chemin absolu ou juste la commande / on s'en fout en vrai.
	//aller cherche la commande dans le path ou bulitin ??
    if (leftfd[0] != -1)
    {
        ft_putstr_fd("prev_fd != 0\n", 1);
        dup2(leftfd[0], STDIN_FILENO);
		close(leftfd[0]);
    }
    if (cmd->type == 1)
    {
		ft_putstr_fd("la commnde est suivie d'un pipe\n", 1);
        dup2(rightfd[1], STDOUT_FILENO);
		close(rightfd[1]);
	}
    if (cmd->infile)
    {
        infd = open (cmd->infile, O_RDONLY);
        if (infd == -1)
            ft_putstr_fd("erreur open du fichier\n", 2);
        dup2(infd, STDOUT_FILENO);
        close(infd);
    }
    if (cmd->outfile)
    {
        outfd = open (cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outfd == -1)
            ft_putstr_fd("erreur open du fichier\n", 2);
        dup2(outfd, STDOUT_FILENO);
        close(outfd);
    }
    pid1 = fork();
    if (pid1 == 0)
    {
		ft_putstr_fd("on est dans le fork\n", 1);
		if (cmd->type == 1)
			close(rightfd[0]);
		if (leftfd[0] != -1)
        	close(leftfd[0]);
        cmd_path = ft_parse(cmd);
        // builtin ou pas
        //changer les outputs input
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("stdin actif \n", 1);
        if(execve(cmd_path, cmd->arg, NULL) == -1)
		{
            ft_putstr_fd("probleme d'execution\n", 2);
			exit(1);
		}
    }
	else
	{
			// lire l'input
	// fermer les fd
	//executer la cmd
	// si built in parent process
	// si exe child process
	// (remettre les inputs et outputs normalement)
	    
        // close(rightfd[0]);
		if (rightfd[0] != -1)
        	close(rightfd[0]);
		if (leftfd[0] != -1)
        	close(leftfd[0]);
        // close(leftfd[1]);
		dup2(stdin, STDIN_FILENO);
        dup2(stdout, STDOUT_FILENO);
		close(stdin);
		close(stdout);

	}


    return (pid1);
}

int main(int ac, char **av, char **env)
{
    t_cmd *cmd_list = NULL;

    // Simulation de commandes
    char **cmd1 = malloc(3 * sizeof(char *));
    cmd1[0] = strdup("cat");
    // cmd1[1] = strdup("-l");
    cmd1[1] = NULL;

    char **cmd2 = malloc(3 * sizeof(char *));
    cmd2[0] = strdup("ls");
    // cmd2[1] = strdup("minishell");
    cmd2[1] = NULL;

    // char **cmd3 = malloc(3 * sizeof(char *));
    // cmd3[0] = strdup("ls");
    // // cmd3[1] = strdup("13");
    // cmd3[1] = NULL;

    // Ajout des commandes à la liste
    add_cmd(&cmd_list, cmd1, NULL, NULL, 0, 1);   // ls -l > output.txt
    add_cmd(&cmd_list, cmd2, NULL, NULL, 0, 0); // grep main < output.txt >> final.txt
    // add_cmd(&cmd_list, cmd3, NULL, NULL, 0, 0);
    
    execution(cmd_list);
    // Affichage des commandes
    // print_cmds(cmd_list);
    

    // Libération de la mémoire
    free_cmds(cmd_list);
    return 0;
}
