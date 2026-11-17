/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:31:42 by masase            #+#    #+#             */
/*   Updated: 2025/04/21 14:38:02 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_double_quote_here_doc(char *str)
{
	int	last_char;

	last_char = ft_strlen(str) - 1;
	if (ft_strlen(str) == 1 && str[0] == '$')
		return (0);
	else if (str[0] == '"' && str[last_char] == '"')
		return (VALID);
	else if (ft_strlen(str) >= 1 && str[0] != '\'')
		return (VALID);
	return (0);
}

char	*find_var_here_doc(t_shell *shell, char *str, t_var *temp)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			new_arg(shell, str, &i);
			if (special_cases(shell, str + i, &i) == VALID)
				continue ;
			search_var_here_doc(shell, str, &i, temp);
			shell->exp.start = i;
		}
		else
			i++;
	}
	return (result_here_doc(shell, str, &i));
}

int	search_var_here_doc(t_shell *shell, char *str, int *i, t_var *temp)
{
	int		var_found;

	only_dolls(shell, str + *i);
	var_found = 0;
	if (search_local_var(shell, str + *i, temp) == VALID)
		var_found = 1;
	else if (search_export_var(shell, str + *i) == VALID)
		var_found = 1;
	if (var_found)
		*i += shell->exp.size_var + 1;
	else
	{
		*i += shell->exp.size_var + 1;
		shell->exp.size_var = 0;
	}
	return (0);
}

char	*result_here_doc(t_shell *shell, char *str, int *i)
{
	char	*line;

	if (str[*i] == '\0' && shell->exp.new == NULL)
		return (0);
	else if (str[shell->exp.start] != '\0')
	{
		shell->exp.tmp = shell->exp.new;
		shell->exp.new = ft_strjoin(shell->exp.new,
				str + shell->exp.start);
		free(shell->exp.tmp);
	}
	if (shell->exp.new)
	{
		free(str);
		line = ft_strdup(shell->exp.new);
		free(shell->exp.new);
		shell->exp.new = NULL;
		return (line);
	}
	return (NULL);
}

int	only_dolls_here_doc(t_shell *shell, char *cur)
{
	shell->exp.size_var = var_size(cur);
	if (shell->exp.size_var == 0)
	{
		shell->exp.tmp = shell->exp.new;
		shell->exp.new = ft_strjoin(shell->exp.new, "$");
		free(shell->exp.tmp);
	}
	return (0);
}
