/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:49:23 by masase            #+#    #+#             */
/*   Updated: 2025/03/12 16:47:04 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void free_shell(t_shell *shell)
{
	if (shell->env)
		free_tab(shell->env);
	if (shell->cmd)
		free_cmds(&shell->cmd);
	// if (shell->tokken)
	// 	free_list(shell->tokken);
	// if (shell->input)
	// 	free(shell->input);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

// Fonction pour libérer la liste de cmd
void free_cmds(t_cmd **head)
{
	t_cmd *tmp;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		if (tmp->arg)
			free_tab(tmp->arg);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);
		if (tmp->delimiter)
			free(tmp->delimiter);
		free(tmp);
		tmp = NULL;
	}
}