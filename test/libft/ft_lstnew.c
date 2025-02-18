/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:44:34 by dchellen          #+#    #+#             */
/*   Updated: 2025/02/11 16:08:19 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*pt_nb;

	pt_nb = (t_list *)malloc(sizeof(t_list));
	if (pt_nb == NULL)
		return (NULL);
	pt_nb->content = content;
	pt_nb->next = NULL;
	return (pt_nb);
}

// int main(void)
// {
//     // Créer une variable pour le contenu
//     int value = 10;

//     // Créer un nouveau nœud en passant l'adresse de value
//     t_list *new_node = ft_lstnew(&value);

//     // Vérifie si le nœud a été créé avec succès
//     if (new_node != NULL)
//     {
//         // Affiche le contenu du nœud
//         printf("nœud : %d\n", *(int *)new_node->content);
//         // Vérifie si next est NULL
//         if (new_node->next == NULL)
//             printf("Le prochain nœud est NULL.\n");
//         // N'oublie pas de libérer la mémoire après utilisation
//         free(new_node); // Libère la mémoire allouée pour le nœud
//     }
//     else
//     {
//         printf("Échec de la création du nœud.\n");
//     }

//     return 0;
// }
