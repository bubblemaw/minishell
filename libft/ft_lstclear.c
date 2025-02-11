/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:22:33 by dchellen          #+#    #+#             */
/*   Updated: 2024/10/24 13:38:37 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*actu;
	t_list	*suivant;

	if (lst == NULL || *lst == NULL)
		return ;
	actu = *lst;
	while (actu != NULL)
	{
		suivant = actu->next;
		del(actu->content);
		free(actu);
		actu = suivant;
	}
	*lst = NULL;
	return ;
}
