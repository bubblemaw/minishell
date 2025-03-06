/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:29:51 by maw               #+#    #+#             */
/*   Updated: 2025/03/06 17:37:30 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_cmd_lst(t_cmd **head)
{
	t_cmd *new_cmd;
	t_cmd *tmp;
	
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return;
	if (!*head)
		*head = new_cmd;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
}
