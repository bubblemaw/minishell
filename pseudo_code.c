/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:16:38 by maw               #+#    #+#             */
/*   Updated: 2025/02/13 18:39:02 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execution(t_cmd *cmd)
{
    int     leftfd[2];
    int     rightfd[2];

    leftfd[0] = -1;
    leftfd[1] = -1;
    ft_putstr_fd("ton pere\n", 1);
	while(cmd)
	{
        if (cmd->type == 1)
        {
            if (pipe(rightfd) == -1)
                ft_putstr_fd("erreur de pipe\n", 2);
        }
		execute_cmd(cmd, leftfd, rightfd);
        leftfd[0] = rightfd[0];
        leftfd[1] = rightfd[1];
		//iterate trough commands
		cmd = cmd->next;
	}

	return (1);
}

int execute_cmd(t_cmd *cmd, int *leftfd, int *rightfd)
{
    char *cmd_path;
    int     infd;
    int     outfd;
    pid_t   pid1;
    int status;

    status = 0;
    cmd_path = NULL;
	//chemin absolu ou juste la commande / on s'en fout en vrai.
	//aller cherche la commande dans le path ou bulitin ??
    pid1 = fork();
    if (pid1 == 0)
    {
        ft_putstr_fd("on est dans le fork\n", 1);
        cmd_path = ft_parse(cmd);
        // builtin ou pas
        //changer les outputs input
        if (leftfd[0] != -1)
        {
            ft_putstr_fd("prev_fd != 0\n", 1);
            dup2(leftfd[0], STDIN_FILENO);
            close(leftfd[0]);
            close(leftfd[1]);
        }
        if (cmd->type == 1)
        {
            dup2(rightfd[1], STDOUT_FILENO);
            close(rightfd[0]);
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
        // dup2(STDIN_FILENO, stdin);
        // dup2(STDOUT_FILENO, stdout);
        // ft_putstr_fd("on va executer\n", STDOUT_FILENO);
        if(execve(cmd_path, cmd->arg, NULL) == -1)
            ft_putstr_fd("probleme d'execution\n", 2);
    }

	// lire l'input
	// fermer les fd
	//executer la cmd
	// si built in parent process
	// si exe child process
	// (remettre les inputs et outputs normalement)
        // close(rightfd[0]);
        close(rightfd[1]);
        close(leftfd[0]);
        close(leftfd[1]);
        pid1 = wait(&status);
        // if (status != 0)
        // {
        //     ft_putstr_fd("problemem au pid wait\n", 2);
        //     return (0);
        // }
    return (1);
}

int main(int ac, char **av, char **env)
{
    t_cmd *cmd_list = NULL;

    // Simulation de commandes
    char **cmd1 = malloc(3 * sizeof(char *));
    cmd1[0] = strdup("ls");
    cmd1[1] = strdup("-l");
    cmd1[2] = NULL;

    char **cmd2 = malloc(3 * sizeof(char *));
    cmd2[0] = strdup("grep");
    cmd2[1] = strdup("minishell");
    cmd2[2] = NULL;

    // char **cmd3 = malloc(3 * sizeof(char *));
    // cmd3[0] = strdup("grep");
    // cmd3[1] = strdup("minishell.h");
    // cmd3[2] = NULL;

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