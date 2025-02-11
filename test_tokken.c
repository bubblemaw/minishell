/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:02:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/02/11 18:09:17 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int skip_space(char *str)
{
	int i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (0);
}

int creat_tokken(char *input, t_shell *shell)
{
	int i;

	i = 0;
	while (input[i] != '\0')
	{
		i++;
	}
	return (0);
}

t_list	*creat_node(t_shell *shell, void *content)
{
	shell->tokken = (t_list *)malloc(sizeof(t_list));
	if (shell->tokken == NULL)
		return (NULL);
	shell->tokken->value = content;
	shell->tokken->next = NULL;
	return (shell->tokken);
}

void	add_node(t_shell *shell, t_list *new)
{
	t_list	*current;

	if (new == NULL)
		return ;
	if (shell->tokken == NULL)
	{
		shell->tokken = new;
		return ;
	}
	current = shell->tokken;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
	return ;
}

int	main (void)
{
	t_shell shell;
	char *input;

	while (1)
	{
		input = readline("minishell$ ");
		if (strncmp(input, "exit ", 4) == 0)
		{
			free(input);
			return (0);
		}
	}
	return (0);
}
