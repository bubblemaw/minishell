/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste_chaine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:17:50 by maw               #+#    #+#             */
/*   Updated: 2025/03/08 16:20:13 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Fonction pour afficher les commandes stockées
void print_cmds(t_cmd *head)
{
	t_cmd *current;

	current = head;
	while (current)
	{
		printf("Commande : ");
		for (int i = 0; current->arg[i]; i++)
			printf("%s ", current->arg[i]);
		printf("\n");
		printf("Fichier d'entrée : %s\n", current->infile ? current->infile : "Aucun");
		printf("Fichier de sortie : %s (%s)\n",
			   current->outfile ? current->outfile : "Aucun",
			   current->append ? "Append" : "Truncate");
		printf("----------------------\n");
		current = current->next;
	}
}

// Fonction pour libérer la liste
void free_cmds(t_cmd **head)
{
	t_cmd *tmp;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		// if (tmp->arg)
		free_tab(tmp->arg);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);
		if (tmp->delimiter)
			free(tmp->delimiter);
		free(tmp);
		tmp = NULL;
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
