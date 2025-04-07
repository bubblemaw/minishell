/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:47 by maw               #+#    #+#             */
/*   Updated: 2025/04/07 11:23:17 by dchellen         ###   ########.fr       */
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
	// if (ft_strlen(tokken->value) == 3 && tokken->value[1] == '$')
	// 	return (0);
	if (ft_strlen(tokken->value) == 1 && tokken->value[0] == '$')
		return (0);
	else if (tokken->value[0] == '"' && tokken->value[last_char] == '"')
			return (VALID);
	else if (ft_strlen(tokken->value) > 1 && tokken->value[0] != '\'')
		return (VALID);
	return (0);
}

int	find_var(t_shell  *shell, t_token *current)
{
	t_var	*temp;
	int		i;
	int		start;
	char	*tmp;
	char	*add;

	temp = shell->var;
	shell->utils.new_arg = NULL;
	i = 0;
	while (current->value[i] != '\0')
	{
		if (current->value[i] == '$')
		{
			if (shell->utils.new_arg == NULL)
				shell->utils.new_arg = ft_substr(current->value, 0, i);
			else
			{
				add =  ft_substr(current->value, start, i - start);
				tmp = shell->utils.new_arg; 
				shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, add);
				free(tmp);
				free(add);
			}
			if (error_case(shell, current->value + i) == VALID)
			{
				i += 2;
				start = i;
				continue ;
			}
			if (pid_dolls(shell,  current->value + i) == VALID)
			{
				i+= 2;
				start = i;
				continue ;
			}
			shell->utils.size_var = var_size(current->value + i);
			if (shell->utils.size_var == 0)
			{
				tmp = shell->utils.new_arg;
				shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, "$");
				free(tmp);
			}
			search_local_var(shell, current->value + i, temp);
			search_export_var(shell, current->value + i);
			i += shell->utils.size_var + 1;
			start = i;
		}
		else
			i++;
	}
	if (current->value[i] == '\0' && shell->utils.new_arg == NULL)
		return (0);
	else if (current->value[start] != '\0')
	{
		tmp = shell->utils.new_arg;
		shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, current->value + start);
		free(tmp);
	}
	if (shell->utils.new_arg)
	{
		free(current->value);
		current->value = ft_strdup(shell->utils.new_arg);
		free(shell->utils.new_arg);
		shell->utils.new_arg = NULL;
	}
	return (0);
}

int	var_size(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$' && str[1] != '\0')
		str++;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '$' && str[i] != '"')
		i++;
	return (i);
}

int	search_local_var(t_shell *shell, char* str, t_var *temp)
{
	char	*tmp;

	if (str[0] == '$' && str[1] != '\0')
		str++;
	while (temp != NULL)
	{
		if (ft_strncmp(str, temp->name, shell->utils.size_var) == 0
			&& temp->name[shell->utils.size_var] == '\0')
		{
			tmp = shell->utils.new_arg;
			shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, temp->value);
			free(tmp);
			return (VALID);
		}
		temp = temp->next;
	}
	return (0);
}

int	search_export_var(t_shell *shell, char* str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	if (str[0] == '$' && str[1] != '\0')
		str++;
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
			tmp = shell->utils.new_arg; 
			shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, shell->env[i] + j);
			free(shell->utils.sub_env);
			free(tmp);
			return (0);
		}
		free(shell->utils.sub_env);
		i++;
	}
	return (0);
}
