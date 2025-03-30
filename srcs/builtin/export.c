/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:19:16 by david             #+#    #+#             */
/*   Updated: 2025/03/30 21:29:54 by david            ###   ########.fr       */
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
        if (check_double_export(token->arg[j], shell) == VALID)
            j++;
        shell->env[*i] = ft_strdup(token->arg[j]);
        (*i)++;
        j++;
    }
    shell->env[*i] = NULL;
    return (0);
}

int check_double_export(char *var, t_shell *shell)
{
    int i;
    int j;

    i = 0;
    while (shell->env[i] != NULL)
    {
        j = 0;
        while (shell->env[i][j] != '=')
            j++;
        if (strncmp(var, shell->env[i], j) == 0)
        {
            shell->env[i] = ft_strdup(var);
            return (VALID);
        }
        i++;
    }
    return (0);
}
