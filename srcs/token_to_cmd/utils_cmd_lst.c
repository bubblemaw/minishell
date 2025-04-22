/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:17:50 by maw               #+#    #+#             */
/*   Updated: 2025/04/22 22:43:36 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Fonction pour afficher les commandes stockées
// void	print_cmds(t_cmd **head)
// {
// 	t_cmd	*current;

// 	current = *head;
// 	while (current)
// 	{
// 		printf("Commande : ");
// 		if (current->arg)
// 		{
// 			for (int i = 0; current->arg[i]; i++)
// 				printf("%s ", current->arg[i]);
// 		}
// 		printf("\n");
// 		printf("d'entrée : %s\n", current->infile ? current->infile : "");
// 		printf("Fichier de sortie : %s (%s)\n",
// 			   current->outfile ? current->outfile : "Aucun",
// 			   current->append ? "Append" : "Truncate");
// 		printf("Deli : %s\n", current->delimiter ? current->delimiter : "");
// 		printf("Pipe : %d\n", current->type ? current->type : 0);
// 		printf("VALID : %d\n", current->valid ? current->valid : 0);
// 		printf("----------------------\n");
// 		current = current->next;
// 	}
// }

int	lst_size(t_cmd *cmd)
{
	t_cmd	*copy;
	int		i;

	copy = cmd;
	i = 0;
	while (copy)
	{
		copy = copy->next;
		i++;
	}
	return (i);
}

t_cmd	*end_list(t_cmd *head)
{
	while ((head)->next)
		head = (head)->next;
	return (head);
}
