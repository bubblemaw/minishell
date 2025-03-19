/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_local.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:44:05 by dchellen          #+#    #+#             */
/*   Updated: 2025/03/19 17:45:03 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int init_var_local(t_shell *shell)
{
    t_token *temp;
    t_var   *exist_var;
    bool    send;

    temp = shell->tokken;
    send = false;
	if (temp->type == COMMAND)
		return (0);
    while (temp != NULL)
    {
        if (temp->type == NAME)
            exist_var = check_doubles(shell->var, temp->value);
        else if (send == true && temp->type == VALUE)
        {
			if (exist_var != NULL)
				replace_var(exist_var, temp);
			else
				creat_var_list(shell, temp);
			send = false;
        }
        else if (temp->type == EQUALITY)
            send = true;
        temp = temp->next;
    }
    return (0);
}

t_var *check_doubles(t_var *check, char *name)
{
	while (check != NULL)
	{
		if (ft_strncmp(check->name, name, strlen(name)) == 0)
			return(check);
		check = check->next;
	}
	return (NULL);
}

void	replace_var(t_var *exist_var, t_token *temp)
{
	free(exist_var->value);
	exist_var->value = strdup(temp->value);
	return ;
}

void	creat_var_list(t_shell *shell, t_token *temp)
{
	shell->creat.new_var = creat_node_var(temp->prev->prev->value, temp->value);
	add_node_var(shell, shell->creat.new_var);
	return ;
}

t_var	*creat_node_var(char *name, char *content)
{
	t_var	*new_var;

	new_var = (t_var *)malloc(sizeof(t_var));
	if (new_var == NULL)
		return (NULL);
	new_var->name = ft_strdup(name);
	new_var->value = ft_strdup(content);
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
		free(head->value);
		free(head->name);
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
			i, current->value);
		current = current->next;
		i++;
	}
}
