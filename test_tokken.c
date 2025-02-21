/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:02:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/02/22 00:56:38 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_space(char *str, int *i)
{
	int check_first;

	check_first = *i;
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
	{
		if (str[*i] == '\0')
			return (0);
		(*i)++;
	}
	if (check_first == 0 &&
		(str[*i] == '=' || str[*i] == '|'))
		return (ERROR);
	return (0);
}

int quotes_conditions_1(char *str, int *i)
{
	if (str[*i - 1] != '=' && str[*i - 1] != ' '
		&& str[*i - 1] != '<' && str[*i - 1] != '>'
		&& str[*i - 1] != '|')
		return (ERROR);
	return (0);
}

int quotes_conditions_2(char *str, int *i)
{
	if (str[*i + 1] != ' '
		&& str[*i + 1] != '<' && str[*i + 1] != '>'
		&& str[*i + 1] != '|' && str[*i + 1] != '\0')
		return (ERROR);
	return (0);
}

int	double_quotes(char *str, int *i)
{
	if (str[*i] == '"')
	{
		// if (quotes_conditions_1(str, i) == ERROR)
		// 	return (ERROR);
		(*i)++;
		while (str[*i] != '"')
			(*i)++;
		if (str[*i] == '"')
		{
			// if (quotes_conditions_2(str, i) == ERROR)
			// 	return (ERROR);
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
		// if (quotes_conditions_1(str, i) == ERROR)
		// 	return (ERROR);
		(*i)++;
		while (str[*i] != '\'')
			(*i)++;
		if (str[*i] == '\'')
		{
			// if (quotes_conditions_2(str, i) == ERROR)
			// 	return (ERROR);
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
		return (VALID);
	}
	else if (str[*i] == '|' || str[*i] == '=')
	{
		if (str[next +1] == '|')
			return (ERROR);
		else if (str[*i] == '=' && 
			(str[*i + 1] == ' ' || str[*i - 1] == ' '
			|| str[*i + 1] == '=' || str[*i - 1] == '='))
			return (ERROR);
		return (VALID);
	}
	return (0);
}

int detect_command(char *input, int *i)
{
	while (input[*i] != ' ' && input[*i] != '>'
		&& input[*i] != '<' && input[*i] != '|'
		// && input[*i] != '"' && input[*i] != '\'' 
		&& input[*i] != '=' && input[*i] != '\0')
		(*i)++;
	if (input[*i] != ' ' && input[*i] != '>'
		&& input[*i] != '<' && input[*i] != '|'
		&& input[*i] != '=' && input[*i] != '\0')
		return (ERROR);
	return (VALID);
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

void free_list(t_chain *head)
{
    t_chain *tmp;

    while (head != NULL)
    {
        tmp = head;
        free(head->value);
        head = head->next;
        free(tmp);
    }
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
	char	*last_token;
	t_chain	*new;

	i = 0;
	end = 0;
	while (input[i] != '\0')
	{
		if (skip_space(input, &i) == ERROR)
			return (ERROR);
		if (input[i] == '\0')
			break ;
		begin = i;
		if (double_quotes(input, &i) == VALID)
			end = i;
		// else if (double_quotes(input, &i) == ERROR)
		// 	return (ERROR);
		else if (single_quotes(input, &i) == VALID)
			end = i;
		// else if (single_quotes(input, &i) == ERROR)
		// 	return (ERROR);
		else if (detect_redirections(input, &i) == ERROR)
			return (ERROR);
		else if (detect_redirections(input, &i) == VALID)
		{
			end = i + 1;
			i++;
		}
		else if (detect_command(input, &i) == VALID)
			end = i;
		else if (detect_command(input, &i) == ERROR)
			return (ERROR);
		content = ft_substr(input, begin, end - begin);
		new = creat_node(content);
		add_node(shell, new);
	}
	last_token = content;
	if (last_token[0] == '<' || last_token[0] == '>'
		|| last_token[0] == '|')
		return (ERROR);
	printf("\n");
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
		if (shell.tokken != NULL)
		{
			free_list(shell.tokken);
			shell.tokken = NULL;
		}
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
