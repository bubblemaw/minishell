/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:29:51 by maw               #+#    #+#             */
/*   Updated: 2025/03/18 17:25:03 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void add_cmd_lst(t_cmd **head)
{
	t_cmd *new_cmd;
	t_cmd *tmp;
	
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return;
	if (!*head)
	{
		*head = new_cmd;
		new_cmd->next = NULL;
	}	
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->next = NULL;
	}
}
void add_cmd_lst_debut(t_cmd **head)
{
	t_cmd *new_cmd;
	// t_cmd *tmp;
	
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return;
	if (!*head)
	{
		*head = new_cmd;
		new_cmd->next = NULL;
	}	
	else
	{
		new_cmd->next = *head;
		*head = new_cmd;
		// tmp = *head;
		// while (tmp->next)
		// 	tmp = tmp->next;
		// tmp->next = new_cmd;
		// new_cmd->next = NULL;
	}
}

void setup_cmd_lst(t_cmd **cmd)
{
	(*cmd)->arg = NULL;
	(*cmd)->infile = NULL;
	(*cmd)->outfile = NULL;
	(*cmd)->delimiter = NULL;
	(*cmd)->type = 0;
	(*cmd)->append = 0;
	(*cmd)->next = NULL;
}
