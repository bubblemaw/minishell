/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:02:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/02/12 11:29:08 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Il faut seprar chaque tokken avec les espaces
// si on detecte des "" ou '' c est considere comme
// un separateur jusqu a ce qu on le retrouve
// mettre un flag begin et end pour savoir de ou a ou va le mot dans le string
// injecter cette partie du string dans un noeud de la liste chainee
// pour injecter le noeud il faut faire un strdup de la partie du string
// que l on souhaite prendre

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
	if (str[*i] == '"')
		(*i)++;
	return (0);
}

int	single_quotes(char *str, int *i)
{
	while (str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	return (0);
}

int creat_tokken(char *input, t_shell *shell)
{
	int *i;
	int begin;
	int end;

	*i = 0;
	begin = 0;
	end = 0;
	while (input[*i] != '\0')
	{
		skip_space(input, &i);
		begin = *i;
		double_quotes(input, &i);
		single_quotes(input, &i);
		(*i)++;
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
