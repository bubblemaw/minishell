/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_local.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:44:05 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/04 16:12:20 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_var_local(t_shell *shell)
{
	t_token	*temp;
	t_var	*exist_var;
	bool	send;

	temp = shell->tokken;
	send = false;
	if (temp->type == COMMAND)
		return (0);
	while (temp != NULL)
	{
		if (temp->type == NAME)
			exist_var = check_doubles(shell->var, temp->value);
		else if (send == true && temp->type == VALUE)
		{
			if (replace_var(exist_var, temp) != VALID)
				creat_var_list(shell, temp);
			send = false;
		}
		else if (temp->type == EQUALITY)
			send = true;
		if (temp->type == NAME)
			crush_export_var(shell, temp->value, temp->next->next->value);
		temp = temp->next;
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
			return(check);
		check = check->next;
	}
	return (NULL);
}

int	replace_var(t_var *exist_var, t_token *temp)
{
	if (exist_var != NULL)
	{
		free(exist_var->value);
		exist_var->value = ft_strdup(temp->value);
		return (VALID);	
	}
	return (0);
}

int	crush_export_var(t_shell *shell, char *name, char *value)
{
	t_shell	*temp;
	int		len;
	int		i;
	char	*new_var;
	char	*tmp;

	temp = shell;
	len = ft_strlen(name);
	i = 0;
	while (temp->env[i] != NULL)
	{
		if (ft_strncmp(name, temp->env[i], len) == 0 && temp->env[i][len] == '=')
		{
			new_var = ft_strdup(name);
			if (!new_var)
				return (-1);
			
			tmp = ft_strjoin(new_var, "=");
			free(new_var);
			if (!tmp)
				return (-1);
			
			new_var = ft_strjoin(tmp, value);
			free(tmp);
			if (!new_var)
				return (-1);
			if (temp->env[i] != NULL)
				free(temp->env[i]);
			temp->env[i] = new_var;
			return (0);
		}
		i++;
	}
	return (0);
}
