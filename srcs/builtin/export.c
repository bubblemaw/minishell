/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:19:16 by david             #+#    #+#             */
/*   Updated: 2025/04/02 11:49:18 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export(t_cmd *token, t_shell *shell)
{
	int		i;
	int		j;
	t_cmd	*current;
	t_shell	*temp;

	i = 0;
	j = 1;
	current = token;
	temp = shell;
	while (current->arg[j] != NULL)
	{
		check_double_export(current->arg[j], temp);
		i++;
		j++;
	}
	return (0);
}

int	join_var(t_token **token)
{
	t_token	*temp;

	(*token)->value = ft_strjoin((*token)->value, (*token)->next->value);
	(*token)->value = ft_strjoin((*token)->value, (*token)->next->next->value);
	temp = (*token)->next;
	(*token)->next = (*token)->next->next->next;
	free(temp->next->value);
	free(temp->next);
	free(temp->value);
	free(temp);
	return (0);
}

int	check_double_export(char *var, t_shell *shell)
{
	int	i;
	int	j;
	int	old_size;

	i = 0;
	old_size = 0;
	while (shell->env[i] != NULL)
	{
		j = 0;
		while (shell->env[i][j] != '=')
			j++;
		if (ft_strncmp(var, shell->env[i], j) == 0 && var[j] == '=' && shell->env[i][j] == '=')
		{
			shell->env[i] = ft_strdup(var);
			crush_local_var(shell, shell->env[i]);
			return (0);
		}
		i++;
	}
	while (shell->env[old_size] != NULL)
		old_size++;
	shell->env = ft_realloc(shell->env, sizeof(char *) * old_size, sizeof(char *) * ( old_size + 1));
	shell->env[i] = ft_strdup(var);
	crush_local_var(shell, shell->env[i]);
	i++;
	shell->env[i] = NULL;
	return (0);
}

int	crush_local_var(t_shell *shell, char *var)
{
	t_var	*temp;
	t_var	*prev;
	int		len;

	temp = shell->var;
	prev = NULL;
	len = 0;
	while (var[len] != '=')
		len++;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->name, var, len) == 0 && temp->name[len] == '\0')
		{
			if (prev == NULL)
				shell->var = temp->next;
			else
				prev->next = temp->next;
			free(temp->name);  
			free(temp->value);
			free(temp);
			return (0);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}
