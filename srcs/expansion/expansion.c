/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:47 by maw               #+#    #+#             */
/*   Updated: 2025/03/23 21:39:27 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_expansion(t_shell *shell)
{
	t_token *current;

	current = shell->tokken;
	while (current != NULL)
	{
		if (current->value[1] == '$' && is_double_quote(current) == VALID)
			find_local_var(shell, current);
		current = current->next;
	}
	return (VALID);
}

int is_double_quote(t_token *tokken)
{
	int last_char;

	last_char = ft_strlen(tokken->value) - 1;
	if (tokken->type == ARGUMENT)
	{
		if (tokken->value[0] == '"' && tokken->value[last_char] == '"')
			return (VALID);
	}
	return (0);
}

int	find_local_var(t_shell  *shell, t_token *current)
{
	t_var 	*temp;
	int		i;
	char	*new_arg;

	temp = shell->var;
	i = 0;
	new_arg = (char *)malloc(sizeof(char) * (ft_strlen(current->value) + 1));
	while (current->value[i] != '\0')
	{
		while (temp != NULL)
		{
			if (ft_strncmp(current->value[i], temp->name, strlen(temp->name)) == 0)
			{
				return (0);
			}
			temp = temp->next;
		}
	}
	return (0);
}

int	change_var_local(t_shell  *shell, t_token *current)
{
	return (0);
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
