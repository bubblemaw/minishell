/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_local.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:44:05 by dchellen          #+#    #+#             */
/*   Updated: 2025/03/27 16:17:10 by david            ###   ########.fr       */
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
	if (temp->type == COMMAND && ft_strncmp(temp->value, "export", 6) != 0)
		return (0);
    printf("ENTER\n");
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
