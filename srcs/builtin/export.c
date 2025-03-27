/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:19:16 by david             #+#    #+#             */
/*   Updated: 2025/03/27 17:15:24 by david            ###   ########.fr       */
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
    temp->env = ft_realloc(temp->env, sizeof(char *) * old_size, sizeof(char *) * (new_path_size(current, temp) + 1));
    while (i < old_size)
        i++;
    add_var_env(current, temp, &i);
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

int add_var_env(t_cmd *token, t_shell *shell, int *i)
{
    int j;

    j = 1;
    while (token->arg[j] != NULL)
    {
        shell->env[*i] = ft_strdup(token->arg[j]);
        printf("NEW LINE : %s\n", shell->env[*i]);
        (*i)++;
        printf("i : %d\n", (*i));
        j++;
    }
    shell->env[*i] = NULL;
    return (0);
}
