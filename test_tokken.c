/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:02:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/02/19 17:28:19 by david            ###   ########.fr       */
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
			return (VALID);
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
			return (VALID);
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
		if (str[next +1] == '|')
			return (ERROR);
		return (VALID);
	}
	return (0);
}

int detect_command(char *input, int *i)
{
	while (input[*i] != ' ' && input[*i] != '>'
		&& input[*i] != '<' && input[*i] != '|'
		&& input[*i] != '\0')
		(*i)++;
	if (input[*i] != ' ' && input[*i] != '>'
		&& input[*i] != '<' && input[*i] != '|'
		&& input[*i] != '\0')
		return (ERROR);
	else 
		return (VALID);
	return (0);
}

t_chain *creat_node(char *content)
{
    t_chain *new;

    new = (t_chain *)malloc(sizeof(t_chain));
    if (new == NULL)
        return (NULL);
    new->value = content;
    new->prev = NULL;
    new->next = NULL;
    return (new);
}

void	add_node(t_shell *shell, t_chain *new)
{
	t_chain	*current;

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
	new->prev = current;
	return ;
}

void	print_chain(t_chain *head)
{
	t_chain	*current;
	int i;

	current = head;
	i = 0;
	while (current != NULL)
	{
		printf("node[%d] -> %s\n", i, current->value);
		current = current->next;
		i++;
	}
}

int	creat_tokken(char *input, t_shell *shell)
{
	int		i;
	int		begin;
	int		end;
	char	*content;
	t_chain	*new;
	
	i = 0;
	end = 0;
	while (input[i] != '\0')
	{
		skip_space(input, &i);
		begin = i;
		if (double_quotes(input, &i) == VALID)
			end = i;
		else if (single_quotes(input, &i) == VALID)
			end = i;
		else if (detect_redirections(input, &i) == ERROR)
			return (ERROR);
		else if (detect_redirections(input, &i) == VALID)
			end = i + 1;
		else if (detect_command(input, &i) == VALID)
			end = i;
		else if (detect_command(input, &i) == ERROR)
			return (ERROR);
		content = ft_substr(input, begin, end - begin);
		new = creat_node(content);
		add_node(shell, new);
		printf("tokken : %s\n", content);
		i++;
	}
	printf("\n---------------------\n");
	print_chain(shell->tokken);
	return (0);
}

int	main (void)
{
	char *input;
	t_shell shell;

	ft_memset(&shell, 0, sizeof(t_shell));
	while (1)
	{
		input = readline("minishell$ ");
		if (strncmp(input, "exit ", 4) == 0)
		{
			free(input);
			return (0);
		}
		if (creat_tokken(input, &shell) == ERROR)
			printf("Error command not found\n");
	}
	return (0);
}
