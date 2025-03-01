/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:14:26 by david             #+#    #+#             */
/*   Updated: 2025/03/01 21:03:02 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*creat_node(char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->value = content;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	add_node(t_shell *shell, t_token *new)
{
	t_token	*current;

	if (new == NULL)
		return ;
	if (shell->tokken == NULL)
	{
		shell->tokken = new;
		return ;
	}
	current = shell->tokken;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
	new->prev = current;
	return ;
}

void	free_list(t_token *head)
{
	t_token	*tmp;

	while (head != NULL)
	{
		tmp = head;
		free(head->value);
		head = head->next;
		free(tmp);
	}
}

void	print_token(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		printf("node[%d] -> %s -> type : [%d]\n",
				current->index, current->value, current->type);
		current = current->next;
	}
}
