/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_local.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:44:05 by dchellen          #+#    #+#             */
/*   Updated: 2025/03/18 18:05:08 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int init_var_local(t_shell *shell)
{
    t_token *temp;
	t_token *check;
    bool    send;

    temp = shell->tokken;
    send = false;
	if (temp->type == COMMAND)
		return (0);
    while (temp != NULL)
    {
        if (send == true && temp->type == VALUE)
        {
			// comparer toutes les values
			// si elle existe deja ecraser avec la nouvelle
			shell->creat.new_var = creat_node_var(temp->value);
			add_node_var(shell, shell->creat.new_var);
			send = false;
        }
        else if (temp->type == EQUALITY)
            send = true;
        temp = temp->next;
    }
	print_var_local(shell->var);
    return (0);
}

int check_doubles(t_token *check, char *name)
{
	while (check != NULL)
	{
		if (check->type == NAME && ft_strncmp(check->value, name, strlen(name + 1)) == 0)
		{
		}
		check = check->next;
	}
	return (0);
}

t_var	*creat_node_var(char *content)
{
	t_var	*new_var;

	new_var = (t_var *)malloc(sizeof(t_var));
	if (new_var == NULL)
		return (NULL);
	new_var->var = ft_strdup(content);
	new_var->next = NULL;
	return (new_var);
}

void	add_node_var(t_shell *shell, t_var *new)
{
	t_var	*current;

	if (new == NULL)
		return ;
	if (shell->var == NULL)
	{
		shell->var = new;
		return ;
	}
	current = shell->var;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
	return ;
}

void	free_list_var(t_var *head)
{
	t_var	*tmp;

	while (head != NULL)
	{
		tmp = head;
		free(head->var);
		head = head->next;
		free(tmp);
	}
}

void	print_var_local(t_var *head)
{
	t_var	*current;
	int		i;

	current = head;
	i = 0;
	while (current != NULL)
	{
		printf("node[%d] -> %s\n",
			i, current->var);
		current = current->next;
		i++;
	}
}
