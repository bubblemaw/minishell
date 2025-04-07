/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:19:16 by david             #+#    #+#             */
/*   Updated: 2025/04/07 17:39:32 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export(t_cmd *token, t_shell *shell)
{
	int		j;
	t_cmd	*current;
	t_shell	*temp;

	j = 1;
	current = token;
	temp = shell;
	while (current->arg[j] != NULL)
	{
		check_double_export(current->arg[j], temp);
		j++;
	}
	return (0);
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
			printf("REPLACE\n");
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
