/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste_chaine_double.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:20:51 by maw               #+#    #+#             */
/*   Updated: 2025/02/28 11:46:42 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Fonction pour créer un nouveau nœud
t_node* createNode(char *str, int type) {
    t_node *newNode = (t_node*)malloc(sizeof(t_node));
    if (newNode == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    newNode->str = strdup(str); // Copie la chaîne de caractères
    newNode->type = type;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Fonction pour ajouter un nœud à la fin de la liste
t_node* appendNode(t_node *head, char *str, int type) {
    t_node *newNode = createNode(str, type);
    if (head == NULL) {
        return newNode;
    } else {
        t_node *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
        return head;
    }
}

// Fonction pour supprimer un nœud de la liste
t_node* deleteNode(t_node *head, t_node *node) {
    if (node == NULL) return head;

    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    free(node->str);
    free(node);
    return head;
}

// Fonction pour afficher la liste du début à la fin
void printListForward(t_node *head) {
    t_node *current = head;
    while (current != NULL) {
        printf("String: %s, Type: %d\n", current->str, current->type);
        current = current->next;
    }
}
// Fonction pour libérer toute la liste
void freeList(t_node *head) {
    t_node *current = head;
    t_node *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current->str);
        free(current);
        current = nextNode;
    }
}

int main(int ac, char **av, char **env) {
    // Exemple d'utilisation
    t_shell shell;
    t_node *head = NULL;

    init_execution(&shell, env);

    head = appendNode(head, "echo", 1);
    head = appendNode(head, "$cool", DQ);
    head = appendNode(head, "Doubly", 3);
 

    printf("Liste du début à la fin:\n");
    printListForward(head);

    ft_expansion(head, &shell);

    printf("\nListe après l'expansion:\n");
    printListForward(head);

    // Libération de la mémoire
    freeList(head);

    return 0;
}