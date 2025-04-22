/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:17:05 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/22 16:26:52 by david            ###   ########.fr       */
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
	split_name_tokens(&shell->tokken);
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
	else if (*find == true)
		(*temp)->type = ARG;
	else
	{
		i = 0;
		while ((*temp)->value[i] != '\0')
		{
			if ((*temp)->value[i] == '=')
			{
				(*temp)->type = NAME;
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

void split_name_tokens(t_token **temp)
{
    t_token *current = *temp;
    t_token *next_node = NULL;

    while (current != NULL)
    {
        next_node = current->next; // Sauvegarde du prochain noeud avant modification
        
        if (current->type == NAME && ft_strchr(current->value, '=') != NULL)
        {
            char *eq_pos = ft_strchr(current->value, '=');
            size_t left_len = eq_pos - current->value;
            size_t right_len = ft_strlen(eq_pos + 1);

            // Création des 3 nouveaux noeuds
            t_token *left = malloc(sizeof(t_token));
            t_token *eq = malloc(sizeof(t_token));
            t_token *right = malloc(sizeof(t_token));

            if (!left || !eq || !right) {
                free(left); free(eq); free(right);
                current = next_node;
                continue;
            }

            // Initialisation des valeurs et types
            left->value = ft_substr(current->value, 0, left_len);
            left->type = NAME;
            
            eq->value = ft_strdup("=");
            eq->type = EQUALITY;
            
            right->value = ft_substr(current->value, left_len + 1, right_len);
            right->type = VALUE;

            // Configuration des liens
            left->prev = current->prev;
            left->next = eq;
            
            eq->prev = left;
            eq->next = right;
            
            right->prev = eq;
            right->next = current->next;

            // Mise à jour des noeuds voisins
            if (left->prev)
                left->prev->next = left;
            else
                *temp = left; // Si on modifie le premier noeud

            if (right->next)
                right->next->prev = right;

            // Nettoyage de l'ancien noeud
            free(current->value);
            free(current);

            // Si on vient de split, on saute les nouveaux noeuds
            current = right;
        }
        
        current = next_node;
    }
}
