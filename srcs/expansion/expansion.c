/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:47 by maw               #+#    #+#             */
/*   Updated: 2025/03/28 15:54:52 by dchellen         ###   ########.fr       */
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

	i = 0;
	j = 0;
	new_arg = (char *)malloc(sizeof(char) * (ft_strlen(current->value) + 1));
	old_size = ft_strlen(current->value) + 1;
	new_size = ft_strlen(current->value) + 1;
	if (shell->var == NULL)
		shell->utils.empty = true;
	while (current->value[i] != '\0')
	{
		temp = shell->var;
		if (current->value[i] == '$')
		{
			i++;
			if (current->value[i] == ' ')
				return (0);
			else if (shell->utils.empty == true)
			{
				while (current->value[i] != ' ' && current->value[i] != '\0')
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
				temp = temp->next;
			}
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
	while (str[i] != ' ' && str[i] != '\0'
			&& str[i] != '"' && str[i] != '$')
		i++;
	return (i);
}
