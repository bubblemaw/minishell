/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:47 by maw               #+#    #+#             */
/*   Updated: 2025/04/07 18:24:50 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_expansion(t_shell *shell)
{
	t_token	*current;

	current = shell->tokken;
	while (current != NULL)
	{
		if (is_double_quote(current) == VALID && current->type == ARGUMENT)
			find_var(shell, current);
		current = current->next;
	}
	return (VALID);
}

int	is_double_quote(t_token *tokken)
{
	int	last_char;

	last_char = ft_strlen(tokken->value) - 1;
	if (ft_strlen(tokken->value) == 1 && tokken->value[0] == '$')
		return (0);
	else if (tokken->value[0] == '"' && tokken->value[last_char] == '"')
		return (VALID);
	else if (ft_strlen(tokken->value) > 1 && tokken->value[0] != '\'')
		return (VALID);
	return (0);
}

int	find_var(t_shell *shell, t_token *current)
{
	t_var	*temp;
	int		i;

	temp = shell->var;
	i = 0;
	while (current->value[i] != '\0')
	{
		if (current->value[i] == '$')
		{
			new_arg(shell, current->value, &i);
			if (error_case(shell, current->value + i) == VALID)
			{
				i += 2;
				shell->exp.start = i;
				continue ;
			}
			if (pid_dolls(shell, current->value + i) == VALID)
			{
				i += 2;
				shell->exp.start = i;
				continue ;
			}
			shell->exp.size_var = var_size(current->value + i);
			if (shell->exp.size_var == 0)
			{
				shell->exp.tmp = shell->exp.new;
				shell->exp.new = ft_strjoin(shell->exp.new, "$");
				free(shell->exp.tmp);
			}
			if (search_local_var(shell, current->value + i, temp) != VALID)
				search_export_var(shell, current->value + i);
			i += shell->exp.size_var + 1;
			shell->exp.start = i;
		}
		else
			i++;
	}
	if (current->value[i] == '\0' && shell->exp.new == NULL)
		return (0);
	else if (current->value[shell->exp.start] != '\0')
	{
		shell->exp.tmp = shell->exp.new;
		shell->exp.new = ft_strjoin(shell->exp.new, current->value + shell->exp.start);
		free(shell->exp.tmp);
	}
	if (shell->exp.new)
	{
		free(current->value);
		current->value = ft_strdup(shell->exp.new);
		free(shell->exp.new);
		shell->exp.new = NULL;
	}
	return (0);
}

int	new_arg(t_shell *shell, char *value, int *i)
{
	if (shell->exp.new == NULL)
		shell->exp.new = ft_substr(value, 0, *i);
	else
	{
		shell->exp.add = ft_substr(value, shell->exp.start, *i - shell->exp.start);
		shell->exp.tmp = shell->exp.new;
		shell->exp.new = ft_strjoin(shell->exp.new, shell->exp.add);
		free(shell->exp.tmp);
		free(shell->exp.add);
	}
	return (0);
}

int	var_size(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$' && str[1] != '\0')
		str++;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '$' && str[i] != '"' && str[i] != '\'')
		i++;
	return (i);
}

int	search_local_var(t_shell *shell, char *str, t_var *temp)
{
	char	*tmp;

	if (str[0] == '$' && str[1] != '\0')
		str++;
	while (temp != NULL)
	{
		if (ft_strncmp(str, temp->name, shell->exp.size_var) == 0
			&& temp->name[shell->exp.size_var] == '\0')
		{
			tmp = shell->exp.new;
			shell->exp.new = ft_strjoin(shell->exp.new, temp->value);
			free(tmp);
			return (VALID);
		}
		temp = temp->next;
	}
	return (0);
}

int	search_export_var(t_shell *shell, char *str)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = NULL;
	i = 0;
	if (str[0] == '$' && str[1] != '\0')
		str++;
	while (shell->env[i] != NULL)
	{
		j = 0;
		while (shell->env[i][j] != '=')
			j++;
		shell->exp.sub_env = ft_substr(shell->env[i], 0, j);
		if (ft_strncmp(str, shell->exp.sub_env, shell->exp.size_var) == 0
			&& shell->exp.sub_env[shell->exp.size_var] == '\0')
		{
			j++;
			tmp = shell->exp.new;
			shell->exp.new = ft_strjoin(shell->exp.new, shell->env[i] + j);
			free(shell->exp.sub_env);
			free(tmp);
			return (0);
		}
		free(shell->exp.sub_env);
		i++;
	}
	return (0);
}
