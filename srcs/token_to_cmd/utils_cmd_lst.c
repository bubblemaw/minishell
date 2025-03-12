/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:17:50 by maw               #+#    #+#             */
/*   Updated: 2025/03/12 16:34:59 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Fonction pour afficher les commandes stockées
void print_cmds(t_cmd *head)
{
	t_cmd *current;

	current = head;
	while (current)
	{
		printf("Commande : ");
		if (current->arg)
		{
			for (int i = 0; current->arg[i]; i++)
				printf("%s ", current->arg[i]);
		}
		printf("\n");
		printf("Fichier d'entrée : %s\n", current->infile ? current->infile : "Aucun");
		printf("Fichier de sortie : %s (%s)\n",
			   current->outfile ? current->outfile : "Aucun",
			   current->append ? "Append" : "Truncate");
		printf("Delimiter : %s\n", current->delimiter ? current->delimiter : "Aucun");
		printf("----------------------\n");
		current = current->next;
	}
}

int lst_size(t_cmd *cmd)
{
	t_cmd *copy;
	int i;

	copy = cmd;
	i = 0;
	while (copy)
	{
		copy = copy->next;
		i++;
	}
	return (i);
}
