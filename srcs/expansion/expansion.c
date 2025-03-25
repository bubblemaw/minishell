/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:47 by maw               #+#    #+#             */
/*   Updated: 2025/03/25 12:12:26 by david            ###   ########.fr       */
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
			find_local_var(shell, current);
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

int	find_local_var(t_shell  *shell, t_token *current)
{
	t_var 	*temp;
	int		i;
	int		j;
	char	*new_arg;
	int		new_size;
	int		old_size;
	int 	test = 0;

	i = 0;
	j = 0;
	new_arg = (char *)malloc(sizeof(char) * (ft_strlen(current->value) + 1));
	old_size = ft_strlen(current->value) + 1;
	new_size = ft_strlen(current->value) + 1;
	while (current->value[i] != '\0')
	{
		temp = shell->var;
		if (current->value[i] == '$')
		{
			i++;
			if (current->value[i] == ' ')
				return (0);
			else if (temp == NULL)
			{
				while (current->value[i] != ' ' && current->value[i] != '\0')
					i++;
				new_arg[j] = current->value[i];
				j++;
				i++;
			}
			while (temp != NULL)
			{
				if (ft_strncmp(current->value + i, temp->name, var_size(current->value + i)) == 0)
				{
					new_size += ft_strlen(temp->value) - ft_strlen(temp->name);
					new_arg = ft_realloc(new_arg, old_size, new_size);
					old_size = new_size;
					ft_strlcpy(new_arg + j, temp->value, ft_strlen(temp->value) + 1);
					j += ft_strlen(temp->value);
					i += ft_strlen(temp->name);
					break ;
				}
				test++;
				temp = temp->next;
			}
		}
		if (temp == NULL && test > 0)
		{
			while (current->value[i] != ' ' && current->value[i] != '\0')
				i++;
			new_arg[j] = current->value[i];
			j++;
			i++;
		}
		else
		{
			new_arg[j] = current->value[i];
			j++;
			i++;
		}
	}
	new_arg[j] = '\0';
	free(current->value);
	current->value = new_arg;
	return (0);
}

int var_size(char *str)
{
	int i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '"')
		i++;
	return (i);
}

//----------------------------------------------//

int expansion(t_token *tokken, t_shell *shell)
{
	char *var_value;

	var_value = ft_findvar(tokken->value, shell);
	free(tokken->value);
	tokken->value = ft_strdup(var_value);
	free (var_value);
	var_value = NULL;
	return (1);
}

char *ft_findvar(char *var_name, t_shell *shell)
{
	char *var_line;
	char *var_value;
	int var_lenth;
	int	i;

	i = 0;
	var_value = NULL;
	var_lenth = ft_strlen(var_name) - 1;
	while (shell->env[i] && ft_strncmp(var_name + 1, shell->env[i], var_lenth) != 0)
		i++;
	if (shell->env[i] == NULL)
		var_value = ft_strdup("");
	else
	{
		var_line = ft_strdup(shell->env[i]);
		printf("var line:%s\n", var_line);
		var_value = ft_strdup(var_line + var_lenth + 1);
	}
	return(var_value);
}
