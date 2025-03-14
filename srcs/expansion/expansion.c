/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:47 by maw               #+#    #+#             */
/*   Updated: 2025/03/14 16:36:31 by dchellen         ###   ########.fr       */
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

int kill_quotes(t_shell *shell)
{
	t_token *temp;
	char	*stash;
	char	*new;
	char	*tmp;
	int i = 0;
	
	temp = shell->tokken;
	new = NULL;
	while (temp != NULL)
	{
		i = 0;
		while (temp && temp->value[i] != '\0')
		{		
			if (temp->value[i] == '"' || temp->value[i] == '\'')
			{
				size_to_kill(temp, shell);
				stash = ft_substr(temp->value, shell->creat.start, shell->creat.len);
				if (new == NULL)
				{
					new = ft_strdup(stash);
					if (new == NULL)
						return (0);
				}
				else
				{
					tmp = ft_strjoin(new, stash);
					free(new);
					new = tmp;
				}
				i = shell->creat.len + 1;
			}
			i++;
			// if (new)
			// 	printf("%s\n", new);
		}
		if (new)
		{
			free(temp->value);
			temp->value = ft_strdup(new);
			free(new);
			new = NULL;
		}
		// printf("%s\n", new);
		temp = temp->next;
	}
	return (0);
}

void size_to_kill(t_token *token, t_shell *shell)
{
	int i;

	i = 0;
	if (token->value[i] == '\'')
	{
		i++;
		shell->creat.start = i;
		while (token->value[i] != '\'')
			i++;
		shell->creat.len = i - 1;
	}
	else if (token->value[i] == '"')
	{
		i++;
		shell->creat.start = i;
		while (token->value[i] != '"')
			i++;
		shell->creat.len = i - 1;
	}
	return ;
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
