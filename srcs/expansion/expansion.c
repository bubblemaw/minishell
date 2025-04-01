/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:47 by maw               #+#    #+#             */
/*   Updated: 2025/03/31 20:01:14 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_expansion(t_shell *shell)
{
	t_token *current;

	current = shell->tokken;
	while (current != NULL)
	{
		if (is_double_quote(current) == VALID)
			find_var(shell, current);
		current = current->next;
	}
	return (VALID);
}

int is_double_quote(t_token *tokken)
{
	int last_char;

	last_char = ft_strlen(tokken->value) - 1;
	if (tokken->type == ARGUMENT
		&& ft_strlen(tokken->value) == 3 && tokken->value[1] == '$')
		return (0);
	else if (tokken->type == ARGUMENT
		&& ft_strlen(tokken->value) == 1 && tokken->value[0] == '$')
		return (0);
	else if (tokken->type == ARGUMENT
		&& tokken->value[0] == '"' && tokken->value[last_char] == '"')
			return (VALID);
	else if (tokken->type == ARGUMENT && tokken->value[0] != '\'')
		return (VALID);
	return (0);
}

int	find_var(t_shell  *shell, t_token *current)
{
	t_var *temp;
	int i;
	int start;

	temp = shell->var;
	shell->utils.new_arg = NULL;
	i = 0;
	while (current->value[i] != '\0')
	{
		if (current->value[i] == '$')
		{
			if (shell->utils.new_arg == NULL)
				shell->utils.new_arg = ft_substr(current->value, 0, i);
			// if (current->value[i] == '$' && (current->value[i + 1] == ' ' || current->value[i + 1] == '$'))
			// {
			// 	shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, "$");
			// 	i++;
			// 	continue;
			// }
			else
				shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, ft_substr(current->value, start, i - start));
			i++;
			shell->utils.size_var = var_size(current->value + i);
			if (search_local_var(shell, current->value + i, temp) != VALID)
				search_export_var(shell, current->value + i);
			i += shell->utils.size_var;
			start = i;
		}
		else
			i++;
	}
	if (current->value[i] == '\0' && shell->utils.new_arg == NULL)
		return (0);
	else if (current->value[start] != '\0')
		shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, current->value + start);
	free(current->value);
	current->value = shell->utils.new_arg;
	return (0);
}

int var_size(char *str)
{
	int i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '$' && str[i] != '"')
		i++;
	return (i);
}

int search_local_var(t_shell *shell, char* str, t_var *temp)
{
	while (temp != NULL)
	{
		if (ft_strncmp(str, temp->name, shell->utils.size_var) == 0
			&& temp->name[shell->utils.size_var] == '\0')
		{
			shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, temp->value);
			return (VALID);
		}
		temp = temp->next;
	}
	return (0);
}

int search_export_var(t_shell *shell, char* str)
{
	int i;
	int j;

	i = 0;
	while (shell->env[i] != NULL)
	{
		j = 0;
		while (shell->env[i][j] != '=')
			j++;
		shell->utils.sub_env = ft_substr(shell->env[i], 0, j);
		if (ft_strncmp(str, shell->utils.sub_env, shell->utils.size_var) == 0 
			&& shell->utils.sub_env[shell->utils.size_var] == '\0')
		{
			j++;
			shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, shell->env[i] + j);
			free(shell->utils.sub_env);
			return (0);
		}
		i++;
	}
	return (0);
}
