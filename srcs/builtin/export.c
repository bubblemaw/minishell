/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:29:06 by masase            #+#    #+#             */
/*   Updated: 2025/04/21 14:00:39 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export(t_cmd *token, t_shell *shell)
{
	int		j;
	t_cmd	*current;
	t_token	*tmp;

	j = 0;
	current = token;
	tmp = shell->tokken;
	if (token->arg[1] == NULL)
	{
		display_export_sort(shell->env, shell->export);
		return (VALID);
	}
	while (ft_strncmp(tmp->value, "export", 6) != 0)
		tmp = tmp->next;
	while (ft_strncmp(current->arg[j], "export", 6) != 0)
		j++;
	tmp = tmp->next;
	j++;
	make_export(shell, current, tmp, &j);
	return (VALID);
}

int	check_double_export(char *var, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (shell->env[i] != NULL)
	{
		j = 0;
		while (shell->env[i][j] != '=')
			j++;
		if (ft_strncmp(var, shell->env[i], j) == 0
			&& var[j] == '=' && shell->env[i][j] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(var);
			crush_local_var(shell, shell->env[i]);
			return (0);
		}
		i++;
	}
	add_var_env(shell, &i, var);
	crush_local_var(shell, shell->env[i]);
	return (0);
}

int	add_var_env(t_shell *shell, int *i, char *var)
{
	int	old_size;

	old_size = 0;
	while (shell->env[old_size] != NULL)
		old_size++;
	shell->env = ft_realloc(shell->env, sizeof(char *) * old_size,
			sizeof(char *) * (old_size + 2));
	shell->env[*i] = ft_strdup(var);
	shell->env[(*i) + 1] = NULL;
	return (0);
}

int	crush_local_var(t_shell *shell, char *var)
{
	t_var	*temp;
	int		len;

	temp = shell->var;
	len = 0;
	while (var[len] != '=')
		len++;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->name, var, len) == 0 && temp->name[len] == '\0')
		{
			if (shell->crash.prev == NULL)
				shell->var = temp->next;
			else
				shell->crash.prev->next = temp->next;
			free(temp->name);
			free(temp->value);
			free(temp);
			return (0);
		}
		shell->crash.prev = temp;
		temp = temp->next;
	}
	return (0);
}

int	join_var(t_token **token)
{
	t_token	*temp;
	char	*str;

	str = (*token)->value;
	(*token)->value = ft_strjoin((*token)->value, (*token)->next->value);
	free(str);
	str = (*token)->value;
	(*token)->value = ft_strjoin((*token)->value, (*token)->next->next->value);
	free(str);
	temp = (*token)->next;
	(*token)->next = (*token)->next->next->next;
	free(temp->next->value);
	free(temp->next);
	free(temp->value);
	free(temp);
	return (0);
}
