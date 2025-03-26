/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:19:16 by david             #+#    #+#             */
/*   Updated: 2025/03/26 17:39:27 by dchellen         ###   ########.fr       */
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
            printf("%s\n", token->arg[j]);
        j++;
    }
    j--;
    printf("nb de vars : %d\n", j);
    return (i + j);
}

int join_var(t_token **token)
{
    int     new_len;
    t_token *temp;

    new_len = ft_strlen((*token)->value) 
                            + ft_strlen((*token)->next->value)
                            + ft_strlen((*token)->next->next->value
                            + 1);
    (*token)->value = ft_realloc((*token)->value, ft_strlen((*token)->value), new_len);
    ft_strlcat((*token)->value, (*token)->next->value, new_len);
    ft_strlcat((*token)->value, (*token)->next->next->value, new_len);
    temp = (*token)->next;
    (*token)->next = (*token)->next->next;
    free(temp->value);
    free(temp);
    return (0);
}
