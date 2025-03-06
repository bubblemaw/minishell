/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:20:11 by dchellen          #+#    #+#             */
/*   Updated: 2024/10/24 13:38:39 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*handle_null_new(t_list **lst_2, void (*del)(void *))
{
	t_list	*temp;

	while (*lst_2 != NULL)
	{
		temp = *lst_2;
		*lst_2 = (*lst_2)->next;
		del(temp->content);
		free(temp);
	}
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_2;
	t_list	*last_node;
	t_list	*new;

	lst_2 = NULL;
	last_node = NULL;
	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		new = ft_lstnew(f(lst->content));
		if (new == NULL)
			return (handle_null_new(&lst_2, del));
		if (lst_2 == NULL)
			lst_2 = new;
		else
			last_node->next = new;
		last_node = new;
		lst = lst->next;
	}
	return (lst_2);
}
