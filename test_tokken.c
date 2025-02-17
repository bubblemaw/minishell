/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:02:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/02/17 16:30:33 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_space(char *str, int *i)
{
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
		(*i)++;
	return (0);
}

int	double_quotes(char *str, int *i)
{
	if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] != '"')
			(*i)++;
		if (str[*i] == '"')
		{
			(*i)++;
			return (1);
		}
	}
	return (0);
}

int	single_quotes(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'')
			(*i)++;
		if (str[*i] == '\'')
		{
			(*i)++;
			return (1);
		}
	}
	return (0);
}

int detect_redirections(char *str, int *i)
{
	int next;

	next = *i;
	if (str[*i] == '>' || str[*i] == '<')
	{
		if (str[next + 1] == str[*i])
			(*i)++;
		if (str[next + 2] == '>' || str[next + 2] == '<' 
			|| (str[*i] == '>' && str[next + 1] == '<')
			|| (str[*i] == '<' && str[next + 1] == '>'))
			return (ERROR);
		return (1);
	}
	else if (str[*i] == '|')
	{
		if (str[next + 1] == '|')
			return (ERROR);
		return (1);
	}
	return (0);
}

int detect_command(char *input, int *i)
{
	int next;

	next = *i;
	while (input[*i] != ' ' && input[*i] != '>'
		&& input[*i] != '<' && input[*i] != '|'
		&& input[*i] != '\0')
		(*i)++;
	if (input[next + *i] != ' ' && input[next + *i] != '>'
		&& input[next + *i] != '<' && input[next + *i] != '|'
		&& input[next + *i] != '\0')
		return (ERROR);
	else if (input[*i] == ' ' || input[*i] == '>'
		|| input[*i] == '<' || input[*i] == '|'
		|| input[*i] == '\0')
		return (1);
	else 
		return (0);
	return (0);
}

int	creat_tokken(char *input)
{
	int	i;
	int	begin;
	int	end;
	char *new;

	i = 0;
	end = 0;
	skip_space(input, &i);
	begin = i;
	printf("b : %d\n", begin);
	while (input[i] != '\0')
	{
		if (double_quotes(input, &i) == 1)
			end = i;
		else if (single_quotes(input, &i) == 1)
			end = i;
		else if (detect_redirections(input, &i) == ERROR)
			return (ERROR);
		else if (detect_redirections(input, &i) == 1)
			end = i + 1;
		else if (detect_command(input, &i) == 1)
		{
			end = i;
			printf("e : %d\n", end);
			break;
		}
		else if (detect_command(input, &i) == ERROR)
			return (ERROR);
		i++;
		printf("e : %d\n", end);
	}
	printf("i : %d\n", i);
	new = ft_substr(input, begin, end - begin);
	printf("le token est : %s\n", new);
	return (0);
}

// t_list	*creat_node(t_shell *shell, void *content)
// {
// 	shell->tokken = (t_list *)malloc(sizeof(t_list));
// 	if (shell->tokken == NULL)
// 		return (NULL);
// 	shell->tokken->value = content;
// 	shell->tokken->next = NULL;
// 	return (shell->tokken);
// }

// void	add_node(t_shell *shell, t_list *new)
// {
// 	t_list	*current;

// 	if (new == NULL)
// 		return ;
// 	if (shell->tokken == NULL)
// 	{
// 		shell->tokken = new;
// 		return ;
// 	}
// 	current = shell->tokken;
// 	while (current->next != NULL)
// 	{
// 		current = current->next;
// 	}
// 	current->next = new;
// 	return ;
// }

// void	print_list(t_list *head)
// {
// 	t_list	*current;

// 	current = head;
// 	while (current)
// 	{
// 		printf("%s\n", (char *)current->value);
// 		current = current->next;
// 	}
// }

int	main (void)
{
	// t_shell shell;
	char *input;

	while (1)
	{
		input = readline("minishell$ ");
		if (strncmp(input, "exit ", 4) == 0)
		{
			free(input);
			return (0);
		}
		if (creat_tokken(input) == ERROR)
			printf("Error command not found\n");
	}
	return (0);
}
