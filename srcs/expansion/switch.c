/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:30:47 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/21 12:54:04 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	search_local_var(t_shell *shell, char *str, t_var *temp)
{
	char	*tmp;

	if (str[0] == '$' && str[1] != '\0')
		str++;
	while (temp != NULL)
	{
		if (ft_strncmp(str, temp->name, shell->exp.size_var) == 0
			&& temp->name[shell->exp.size_var] == '\0')
		{
			tmp = shell->exp.new;
			shell->exp.new = ft_strjoin(shell->exp.new, temp->value);
			free(tmp);
			return (VALID);
		}
		temp = temp->next;
	}
	return (0);
}

int	search_export_var(t_shell *shell, char *str)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = NULL;
	i = 0;
	if (str[0] == '$' && str[1] != '\0')
		str++;
	while (shell->env[i] != NULL)
	{
		j = 0;
		while (shell->env[i][j] != '=')
			j++;
		shell->exp.sub_env = ft_substr(shell->env[i], 0, j);
		if (ft_strncmp(str, shell->exp.sub_env, shell->exp.size_var) == 0
			&& shell->exp.sub_env[shell->exp.size_var] == '\0')
		{
			search_export_var_2(shell, tmp, &j, i);
			return (VALID);
		}
		free(shell->exp.sub_env);
		i++;
	}
	return (0);
}

void	search_export_var_2(t_shell *shell, char *tmp, int *j, int i)
{
	(*j)++;
	tmp = shell->exp.new;
	shell->exp.new = ft_strjoin(shell->exp.new, shell->env[i] + *j);
	free(shell->exp.sub_env);
	free(tmp);
	return ;
}

int	result(t_shell *shell, t_token *current, int *i)
{
	if (current->value[*i] == '\0' && shell->exp.new == NULL)
		return (0);
	else if (current->value[shell->exp.start] != '\0')
	{
		shell->exp.tmp = shell->exp.new;
		shell->exp.new = ft_strjoin(shell->exp.new,
				current->value + shell->exp.start);
		free(shell->exp.tmp);
	}
	if (shell->exp.new)
	{
		free(current->value);
		current->value = ft_strdup(shell->exp.new);
		free(shell->exp.new);
		shell->exp.new = NULL;
	}
	return (0);
}

int	only_dolls(t_shell *shell, char *cur)
{
	if ((cur[1] == '"' && shell->exp.quot == false)
		|| cur[1] == '\'')
		return (0);
	shell->exp.size_var = var_size(cur);
	if (shell->exp.size_var == 0)
	{
		shell->exp.tmp = shell->exp.new;
		shell->exp.new = ft_strjoin(shell->exp.new, "$");
		free(shell->exp.tmp);
	}
	return (0);
}
