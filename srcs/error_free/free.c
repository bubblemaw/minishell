/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:21:49 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/20 21:51:27 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->env)
		free_tab(shell->env);
	if (shell->cmd)
		free_cmds(&shell->cmd);
	if (shell->tokken)
		free_list(shell->tokken);
	if (shell->var)
		free_list_var(shell->var);
	if (shell->input)
		free(shell->input);
	if (shell->path.pwd)
		free(shell->path.pwd);
	if (shell->path.oldpwd)
		free(shell->path.oldpwd);
	if (shell->export)
		free_tab(shell->export);
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

void	free_cmds(t_cmd **head)
{
	t_cmd	*tmp;

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

int	free_new_redirection(t_shell *shell)
{
	if (shell->redir.prev_infile)
		free(shell->redir.prev_infile);
	if (shell->redir.prev_outfile)
		free(shell->redir.prev_outfile);
	if (shell->redir.prev_delimiter)
		free(shell->redir.prev_delimiter);
	shell->redir.prev_infile = NULL;
	shell->redir.prev_outfile = NULL;
	shell->redir.prev_delimiter = NULL;
	shell->redir.apppend = 0;
	shell->redir.type = 0;
	return (VALID);
}

void	free_split(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return ;
}
