/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:02:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/02/12 17:47:05 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_space(char *str, int *i)
{
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
	{
		(*i)++;
	}
	return (0);
}

int	double_quotes(char *str, int *i)
{
	while (str[*i] != '"')
		(*i)++;
	return (0);
}

int	single_quotes(char *str, int *i)
{
	while (str[*i] != '\'')
		(*i)++;
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

void	print_list(t_list *head)
{
	t_list	*current;

	current = head;
	while (current)
	{
		printf("%s\n", (char *)current->value);
		current = current->next;
	}
}

// main test juste avec ac av pour tester les tokkens
int	main (int ac, char *av[])
{
	t_shell shell;


	return (0);
}



// Ci dessous le main avec le prompt 

// int	main (void)
// {
// 	t_shell shell;
// 	char *input;

// 	while (1)
// 	{
// 		input = readline("minishell$ ");
// 		if (strncmp(input, "exit ", 4) == 0)
// 		{
// 			free(input);
// 			return (0);
// 		}
// 	}
// 	return (0);
// }
