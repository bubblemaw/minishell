/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:16:38 by maw               #+#    #+#             */
/*   Updated: 2025/02/11 22:37:30 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execution(t_cmd *cmd)
{
	while(cmd->next)
	{
		execute(cmd);
		//iterate trough commands
		cmd = cmd->next;
	}
	return (1);
}

int execute(t_cmd *cmd)
{
	//chemin absolu ou juste la commande / on s'en fout en vrai.
	//aller cherche la commande dans le path ou bulitin ??
	// builtin ou pas
	//changer les outputs input
	// lire l'input
	// fermer les fd
	//executer la cmd
	// si built in parent process
	// si exe child process
	// (remettre les inputs et outputs normalement)
}

int main(int ac, char **av, char **env)
{
    t_cmd *cmd_list = NULL;

    // Simulation de commandes
    char **cmd1 = malloc(3 * sizeof(char *));
    cmd1[0] = strdup("ls");
    cmd1[1] = strdup("-l");
    cmd1[2] = NULL;

    char **cmd2 = malloc(2 * sizeof(char *));
    cmd2[0] = strdup("grep");
    cmd2[1] = strdup("main");
    cmd2[2] = NULL;

    // Ajout des commandes à la liste
    add_cmd(&cmd_list, cmd1, NULL, "output.txt", 0);   // ls -l > output.txt
    add_cmd(&cmd_list, cmd2, "output.txt", "final.txt", 1); // grep main < output.txt >> final.txt

    // Affichage des commandes
    print_cmds(cmd_list);

    // Libération de la mémoire
    free_cmds(cmd_list);
    return 0;
}