/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:17:05 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/23 10:31:18 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	creat_list(t_shell *shell, char *input)
{
	shell->creat.content = ft_substr(input, shell->creat.begin,
			shell->creat.end - shell->creat.begin);
	shell->creat.new = creat_node(shell->creat.content);
	add_node(shell, shell->creat.new);
	return (0);
}

int	give_token_data(t_shell *shell)
{
	t_token	*temp;

	temp = shell->tokken;
	first_case(shell, &temp);
	shell->creat.find = false;
	shell->creat.com = NULL;
	while (temp != NULL)
	{
		if (give(shell, &temp, &shell->creat.find) == ERROR)
			return (ERROR);
		temp = temp->next;
	}
	temp = shell->tokken;
	// export_kill(shell);
	return (0);
}

void	first_case(t_shell *shell, t_token **temp)
{
	shell->creat.first = ft_strdup((*temp)->value);
	if (shell->creat.first[0] == '<' || shell->creat.first[0] == '>')
	{
		(*temp)->type = REDIRECTION;
		*temp = (*temp)->next;
		(*temp)->type = ARG;
		*temp = (*temp)->next;
	}
	free(shell->creat.first);
	return ;
}

int	give(t_shell *shell, t_token **temp, bool *find)
{
	int i;
	shell->creat.var_flag = false;
	if ((*temp)->value[0] == '>' || (*temp)->value[0] == '<')
		(*temp)->type = REDIRECTION;
	else if ((*temp)->value[0] == '|')
	{
		(*temp)->type = PIPE;
		*find = false;
		shell->creat.com = NULL;
	}
	else if ((*temp)->value[0] == '-' && (*temp)->value[1] != ' ')
		(*temp)->type = OPTION;
	else if (*find == true && ft_strncmp(shell->creat.com, "export", 7) != 0)
		(*temp)->type = ARG;
	else
	{
		i = 0;
		while ((*temp)->value[i] != '\0')
		{
			if ((*temp)->value[i] == '=')
			{
				(*temp)->type = VAR;
				if (var_name_b(shell, (*temp)->value) == ERROR)
					return (ERROR);
				return (0);
			}
			i++;
		}
		(*temp)->type = COMMAND;
		*find = true;
		shell->creat.com = (*temp)->value;
	}
	return (0);
}

// int	give_var(t_shell *shell, t_token **temp, bool *find)
// {
// 	if ((*temp)->value[0] == '=')
// 	{
// 		(*temp)->type = EQUALITY;
// 		if (var_name((*temp)->prev->value) == ERROR
// 			&& ft_strncmp(shell->creat.com, "export", 7) != 0)
// 		{
// 			var_error(shell, *temp);
// 			shell->creat.var_flag = true;
// 			return (ERROR);
// 		}
// 		if ((*temp)->prev->type == COMMAND)
// 			*find = false;
// 		(*temp)->prev->type = NAME;
// 		(*temp)->next->type = VALUE;
// 		*temp = (*temp)->next;
// 	}
// 	return (0);
// }
