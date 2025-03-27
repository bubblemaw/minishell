/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:19:16 by david             #+#    #+#             */
/*   Updated: 2025/03/27 10:38:18 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int export(t_cmd *token, t_shell *shell)
{
    t_cmd   *current;
    t_shell *temp;
    int old_size;
    int i;

    current = token;
    temp = shell;
    old_size = 0;
    i = 0;
    while (temp->env[old_size] != NULL)
        old_size++;
    temp->env = ft_realloc(temp->env, old_size, new_path_size(current, temp));
    while (i <= old_size)
        i++;
    printf("on commence sur : %d\n", i);

    return (0);
}

int new_path_size(t_cmd *token, t_shell *shell)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (shell->env[i] != NULL)
        i++;
    while (token->arg[j] != NULL)
    {
        if (j != 0)
            printf("[%d] %s\n", j, token->arg[j]);
        j++;
    }
    j--;
    printf("nb de vars : %d\n", j);
    return (i + j);
}

int join_var(t_token **token)
{
    t_token *temp;

    (*token)->value = ft_strjoin((*token)->value, (*token)->next->value);
    (*token)->value = ft_strjoin((*token)->value, (*token)->next->next->value);
    temp = (*token)->next;
    (*token)->next = (*token)->next->next->next;
    free(temp->next->value);
    free(temp->next);
    free(temp->value);
    free(temp);
    return (0);
}

int check_double_export(t_cmd *token)
{
    int i;
    int j;

    i = 0;
    while (token->arg[i] != NULL)
    {
        j = i + 1;
        while (token->arg[j] != NULL)
        {
            if (ft_strncmp(token->arg[i], token->arg[j], ft_strlen(token->arg[i])) == 0)
            j++;
        }
    }
    return (0);
}
