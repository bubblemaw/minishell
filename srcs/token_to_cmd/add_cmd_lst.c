/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:29:51 by maw               #+#    #+#             */
/*   Updated: 2025/04/20 14:22:42 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_cmd_lst(t_cmd **head)
{
	t_cmd	*new_cmd;
	t_cmd	*tmp;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return ;
	if (!*head)
	{
		*head = new_cmd;
		new_cmd->next = NULL;
		new_cmd->prev = NULL;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->prev = tmp;
		new_cmd->next = NULL;
	}
}

void	add_cmd_before_last(t_cmd **head)
{
	t_cmd	*new_cmd;
	t_cmd	*current;

	current = *head;
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return ;
	if (!*head)
		*head = new_cmd;
	else if (lst_size(current) == 1)
	{
		current->prev = new_cmd;
		new_cmd->next = current;
		*head = new_cmd;
	}
	else if (lst_size(current) == 2)
		insert_node(current, new_cmd);
	else
	{
		while (current->next->next)
			current = current->next;
		insert_node(current, new_cmd);
	}
}

void	insert_node(t_cmd *current, t_cmd *new_cmd)
{
	new_cmd->next = current->next;
	new_cmd->prev = current;
	current->next->prev = new_cmd;
	current->next = new_cmd;
}

void	setup_cmd_lst(t_cmd **cmd)
{
	(*cmd)->arg = NULL;
	(*cmd)->infile = NULL;
	(*cmd)->outfile = NULL;
	(*cmd)->delimiter = NULL;
	(*cmd)->type = 0;
	(*cmd)->db_flag = 0;
	(*cmd)->append = 0;
	(*cmd)->valid = VALID;
}
