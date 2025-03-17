/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:47 by maw               #+#    #+#             */
/*   Updated: 2025/03/17 15:01:46 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_expansion(t_shell *shell)
{
	t_token *current;

	current = shell->tokken;
	while (current != NULL)
	{
		if (current->value[0] == '$' && is_double_quote(current) == VALID)
			expansion(current, shell);
		current = current->next;
	}
	return (VALID);
}

int is_double_quote(t_token *tokken)
{
	int last_char;

	last_char = ft_strlen(tokken->value) - 1;
	if (tokken->value[0] == '"' && tokken->value[last_char] == '"' )
		return (VALID);
	else 
		return (0);
}

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
