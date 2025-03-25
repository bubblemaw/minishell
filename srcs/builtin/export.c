/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:19:16 by david             #+#    #+#             */
/*   Updated: 2025/03/25 16:24:29 by david            ###   ########.fr       */
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
    while (i < old_size)
        i++;
    // while ()
    // {
    //     temp->env[i] = ft_strdup(current->arg[i]);
    // }
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
        j++;
    return (i + j);
}
