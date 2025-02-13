/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _liste_chaine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:17:50 by maw               #+#    #+#             */
/*   Updated: 2025/02/11 21:26:20 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour créer un nouveau nœud de commande
t_cmd *create_cmd(char **arg, char *infile, char *outfile, int append)
{
    t_cmd *new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
        return NULL;
    new_cmd->arg = arg;
    new_cmd->infile = infile ? strdup(infile) : NULL;
    new_cmd->outfile = outfile ? strdup(outfile) : NULL;
    new_cmd->append = append;
    new_cmd->next = NULL;
    return new_cmd;
}

// Fonction pour ajouter une commande à la liste
void add_cmd(t_cmd **head, char **arg, char *infile, char *outfile, int append)
{
    t_cmd *new_cmd = create_cmd(arg, infile, outfile, append);
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
        free(tmp);
    }
}
