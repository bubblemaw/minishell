/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:55:13 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/14 16:46:10 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int var_name(char *value)
{
    int i;
    
    i = 0;
    if (ft_strlen(value) > 1
        && (ft_isalpha(value[i]) == 0 && value[i] != '_'))
        return (ERROR);
    else if (ft_strlen(value) == 1 && value[i] == '_')
        return (ERROR);
    while (value[i] != '\0')
    {
        if (ft_isalnum(value[i]) == 0 && value[i] != '_')
            return (ERROR);
        i++;
    }
    return (VALID);
}
