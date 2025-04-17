/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:55:13 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/16 21:43:23 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	var_name(t_shell *shell, char *value)
{
	int	i;

	i = 0;
	shell->creat.add = false;
	shell->creat.yes = false;
	if (ft_strlen(value) > 1
		&& (ft_isalpha(value[i]) == 0 && value[i] != '_'))
		return (ERROR);
	else if (ft_strlen(value) == 1 && value[i] == '_')
		return (ERROR);
	while (value[i] != '\0')
	{
		if (ft_isalnum(value[i]) == 0 && value[i] != '_' && value[i] != '='
			&& value[i] != '+')
			return (ERROR);
		if (value[i] == '+' && value[i + 1] != '\0')
			shell->creat.add = true;
		i++;
	}
	if (shell->creat.add == true)
		return (ERROR);
	if(value[i] == '\0' && value[i - 1] == '+')
		shell->creat.yes = true;
	return (VALID);
}

int	var_name_export(char *value)
{
	int		i;
	int		size;
	char	*var;

	i = 0;
	size = 0;
	while (value[size] != '=')
		size++;
	var = ft_substr(value, 0, size);
	if (ft_strlen(var) > 1
		&& (ft_isalpha(var[i]) == 0 && var[i] != '_'))
	{
		free(var);
		return (ERROR);
	}
	else if (ft_strlen(var) == 1 && var[i] == '_')
	{
		free(var);
		return (ERROR);
	}
	while (var[i] != '\0')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_' && var[i] != '=')
		{
			free(var);
			return (ERROR);
		}
		i++;
	}
	free(var);
	return (0);
}

int	export_kill(t_shell *shell)
{
	t_token	*tmp;
	if (ft_strncmp(shell->creat.com, "export", 7) != 0)
		return (0);

	tmp = shell->tokken;
	while (tmp->type == NAME || tmp->type == EQUALITY || tmp->type == VALUE)
	{
		tmp = tmp->next;
	}
	if (ft_strncmp(tmp->value, "export", 7) == 0)
	{
		if (tmp->type != COMMAND)
			tmp->type = COMMAND;
		shell->creat.var_flag = true;
	}
	return (0);
}

int	export_boucle(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokken;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->value, "export", 7) == 0)
			return (VALID);
		tmp = tmp->next;
	}
	return (0);
}

void	var_error(t_shell *shell, t_token *temp)
{
	char	*tmp;

	tmp = NULL;
	shell->creat.err = ft_strjoin(temp->prev->value, temp->value);
	tmp = shell->creat.err;
	shell->creat.err = ft_strjoin(shell->creat.err, temp->next->value);
	free(tmp);
	return ;
}
