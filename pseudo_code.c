/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:16:38 by maw               #+#    #+#             */
/*   Updated: 2025/02/11 16:50:56 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execution(t_cmd *cmd)
{
	while(cmd->next)
	{
		execute();
		//iterate trough commands
	}
	
}

int execute()
{
	//chemin absolu ou juste la commande
	// builtin ou pas
	//changer les outputs input
	// lire l'input
	// fermer les fd
	//executer la cmd
	// si built in parent process
	// si exe child process
	// (remettre les inputs et outputs normalement)

}



