/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_var_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:36:46 by david             #+#    #+#             */
/*   Updated: 2025/04/20 11:56:45 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	creat_var_list(t_shell *shell, t_token *temp)
{
	shell->creat.new_var = creat_node_var(temp->prev->prev->value, temp->value);
	add_node_var(shell, shell->creat.new_var);
	return ;
}

t_var	*creat_node_var(char *name, char *content)
{
	t_var	*new_var;

	new_var = (t_var *)malloc(sizeof(t_var));
	if (new_var == NULL)
		return (NULL);
	new_var->name = ft_strdup(name);
	new_var->value = ft_strdup(content);
	new_var->next = NULL;
	return (new_var);
}

void	add_node_var(t_shell *shell, t_var *new)
{
	t_var	*current;

	if (new == NULL)
		return ;
	if (shell->var == NULL)
	{
		shell->var = new;
		return ;
	}
	current = shell->var;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
	return ;
}

void	free_list_var(t_var *head)
{
	t_var	*tmp;

	while (head != NULL)
	{
		tmp = head;
		free(head->value);
		free(head->name);
		head = head->next;
		free(tmp);
	}
}

void	print_var_local(t_var *head)
{
	t_var	*current;
	int		i;

	current = head;
	i = 0;
	while (current != NULL)
	{
		printf("node[%d] -> %s\n",
			i, current->value);
		current = current->next;
		i++;
	}
}
