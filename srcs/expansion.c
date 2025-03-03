/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:47 by maw               #+#    #+#             */
/*   Updated: 2025/02/28 11:49:48 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_expansion(t_node *node, t_shell *shell)
{
	t_node *current;

	current = node;
	while (current)
	{
		if (current->str[0] == '$' && current->type == DQ)
			expansion(current, shell);
		current = current->next;
	}
	return (1);
}

int expansion(t_node *node, t_shell *shell)
{
	char *var_value;

	var_value = ft_findvar(node->str, shell);
	free(node->str);
	node->str = ft_strdup(var_value);
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
