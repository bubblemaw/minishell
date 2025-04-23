/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_local.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:44:05 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/23 01:57:19 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_var_local(t_shell *shell)
{
	t_token	*temp;
	t_var	*exist_var;
	int		i;
	int		start;
	char	*name;
	char	*value;

	temp = shell->tokken;
	i = 0;
	name = NULL;
	value = NULL;
	if (temp->type == COMMAND)
		return (0);
	while (temp != NULL)
	{
		if (temp->type == VAR)
		{
			while (temp->value[i] != '=')
				i++;
			name = ft_substr(temp->value, 0, i);
			i++;
			start = i;
			while (temp->value[i] != '\0')
				i++;
			value = ft_substr(temp->value, start, i);
			exist_var = check_doubles(shell->var, name);
			if (replace_var(exist_var, value) != VALID)
				creat_var_list(shell, name, value);
			crush_export_var(shell, name, value);
			temp = temp->next;
		}
	}
	return (0);
}

t_var	*check_doubles(t_var *check, char *name)
{
	int	len;

	len = 0;
	while (check != NULL)
	{
		len = ft_strlen(name);
		if (ft_strncmp(check->name, name, len) == 0
			&& check->name[len] == '\0')
			return (check);
		check = check->next;
	}
	return (NULL);
}

int	replace_var(t_var *exist_var, char *value)
{
	if (exist_var != NULL)
	{
		free(exist_var->value);
		exist_var->value = ft_strdup(value);
		return (VALID);
	}
	return (0);
}

int	crush_export_var(t_shell *shell, char *name, char *value)
{
	t_shell	*temp;
	int		len;
	int		i;

	temp = shell;
	len = ft_strlen(name);
	i = 0;
	while (temp->env[i] != NULL)
	{
		if (ft_strncmp(name, temp->env[i], len) == 0
			&& temp->env[i][len] == '=')
		{
			shell->crash.new_var = ft_strdup(name);
			shell->crash.tmp = ft_strjoin(shell->crash.new_var, "=");
			free(shell->crash.new_var);
			shell->crash.new_var = ft_strjoin(shell->crash.tmp, value);
			free(shell->crash.tmp);
			if (temp->env[i] != NULL)
				free(temp->env[i]);
			temp->env[i] = shell->crash.new_var;
			return (0);
		}
		i++;
	}
	return (0);
}
