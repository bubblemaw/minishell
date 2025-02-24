/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste_chaine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:17:50 by maw               #+#    #+#             */
/*   Updated: 2025/02/24 18:34:49 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Fonction pour créer un nouveau nœud de commande
t_token *create_cmd(char **arg, char *infile, char *outfile, int append, int type)
{
    t_token *new_cmd = malloc(sizeof(t_token));
    if (!new_cmd)
        return NULL;
    new_cmd->arg = arg;
    new_cmd->infile = infile ? strdup(infile) : NULL;
    new_cmd->outfile = outfile ? strdup(outfile) : NULL;
    new_cmd->append = append;
    new_cmd->type = type;
    new_cmd->next = NULL;
    return new_cmd;
}

// Fonction pour ajouter une commande à la liste
void add_cmd(t_token **head, char **arg, char *infile, char *outfile, char *delimiter, int append, int type)
{
    t_token *new_cmd = create_cmd(arg, infile, outfile, append, type);
    if (!new_cmd)
        return;
    if (!*head)
        *head = new_cmd;
    else
    {
        t_token *tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_cmd;
    }
}

// Fonction pour afficher les commandes stockées
void print_cmds(t_token *head)
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
void free_cmds(t_token *head)
{
    t_token *tmp;
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

int lst_size(t_token *token)
{
    t_token *copy;
    int i;

    copy = token;
    i = 0;
    while (copy)
    {
        copy = copy->next;
        i++;
    }
    return (i);
}
