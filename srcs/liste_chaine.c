/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste_chaine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:17:50 by maw               #+#    #+#             */
/*   Updated: 2025/03/03 15:46:57 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Fonction pour créer un nouveau nœud de commande
t_cmd *create_cmd(char **arg, char *infile, char *outfile, char *delimiter, int append, int type)
{
    t_cmd *new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
        return NULL;
    new_cmd->arg = arg;
    new_cmd->infile = infile ? strdup(infile) : NULL;
    new_cmd->outfile = outfile ? strdup(outfile) : NULL;
	new_cmd->delimiter = delimiter ? strdup(delimiter) : NULL;
    new_cmd->append = append;
    new_cmd->type = type;
    new_cmd->next = NULL;
    return new_cmd;
}

// Fonction pour ajouter une commande à la liste
void add_cmd(t_cmd **head, char **arg, char *infile, char *outfile, char *delimiter, int append, int type)
{
    t_cmd *new_cmd = create_cmd(arg, infile, outfile, delimiter, append, type);
    if (!new_cmd)
        return;
    if (!*head)
        *head = new_cmd;
    else
    {
        t_cmd *tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_cmd;
    }
}

// Fonction pour afficher les commandes stockées
void print_cmds(t_cmd *head)
{
    while (head)
    {
        printf("Commande : ");
        for (int i = 0; head->arg[i]; i++)
            printf("%s ", head->arg[i]);
        printf("\n");
        printf("Fichier d'entrée : %s\n", head->infile ? head->infile : "Aucun");
        printf("Fichier de sortie : %s (%s)\n",
               head->outfile ? head->outfile : "Aucun",
               head->append ? "Append" : "Truncate");
        printf("----------------------\n");
        head = head->next;
    }
}

// Fonction pour libérer la liste
void free_cmds(t_cmd *head)
{
    t_cmd *tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->arg);  // Supposé alloué dynamiquement
        free(tmp->infile);
        free(tmp->outfile);
		free(tmp->delimiter);
        free(tmp);
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
