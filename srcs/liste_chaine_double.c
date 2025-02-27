/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste_chaine_double.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:20:51 by maw               #+#    #+#             */
/*   Updated: 2025/02/26 19:35:43 by maw              ###   ########.fr       */
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

// Fonction pour initialiser une liste chaînée
DoublyLinkedList* createDoublyLinkedList() {
    DoublyLinkedList *list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if (list == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Fonction pour ajouter un nœud à la fin de la liste
void appendNode(DoublyLinkedList *list, char *str, int type) {
    t_node *newNode = createNode(str, type);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

// Fonction pour supprimer un nœud de la liste
void deleteNode(DoublyLinkedList *list, t_node *node) {
    if (node == NULL) return;

    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    free(node->str);
    free(node);
}

// Fonction pour afficher la liste du début à la fin
void printListForward(DoublyLinkedList *list) {
    t_node *current = list->head;
    while (current != NULL) {
        printf("String: %s, Type: %d\n", current->str, current->type);
        current = current->next;
    }
}

// Fonction pour afficher la liste de la fin au début
void printListBackward(DoublyLinkedList *list) {
    t_node *current = list->tail;
    while (current != NULL) {
        printf("String: %s, Type: %d\n", current->str, current->type);
        current = current->prev;
    }
}

// Fonction pour libérer toute la liste
void freeList(DoublyLinkedList *list) {
    t_node *current = list->head;
    t_node *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current->str);
        free(current);
        current = nextNode;
    }
    free(list);
}

int main() {
    // Exemple d'utilisation
    DoublyLinkedList *list = createDoublyLinkedList();

    appendNode(list, "Hello", 1);
    appendNode(list, "World", 2);
    appendNode(list, "Doubly", 3);
    appendNode(list, "Linked", 4);
    appendNode(list, "List", 5);

    printf("Liste du début à la fin:\n");
    printListForward(list);

    printf("\nListe de la fin au début:\n");
    printListBackward(list);

    // Suppression d'un nœud (par exemple, le deuxième nœud)
    t_node *nodeToDelete = list->head->next;
    deleteNode(list, nodeToDelete);

    printf("\nListe après suppression du deuxième nœud:\n");
    printListForward(list);

    // Libération de la mémoire
    freeList(list);

    return 0;
}