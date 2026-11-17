/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:14:26 by david             #+#    #+#             */
/*   Updated: 2025/04/20 12:14:27 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	int		i;

	current = head;
	i = 0;
	while (current != NULL)
	{
		printf("node[%d] -> %s -> type : [%d]\n",
			i, current->value, current->type);
		current = current->next;
		i++;
	}
}
