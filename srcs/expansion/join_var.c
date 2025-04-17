/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:49:44 by david             #+#    #+#             */
/*   Updated: 2025/04/16 21:43:20 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int add_var_loc(t_var *check, char *name)
// {
    
//     return ();
// }

int sub_var_size(char *name)
{
    int i;

    i = 0;
    while (name[i] != '\0')
        i++;
    if (name[i - 1] == '+')
    i--;
    return (i);
}
