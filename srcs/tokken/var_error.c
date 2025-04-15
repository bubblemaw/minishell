/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:55:13 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/15 12:19:39 by dchellen         ###   ########.fr       */
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
        if (ft_isalnum(value[i]) == 0 && value[i] != '_' && value[i] != '=')
            return (ERROR);
        i++;
    }
    return (VALID);
}

int var_name_export(char *value)
{
    int i;
    int size;
    char *var;
    
    i = 0;
    size = 0;
    while (value[size] != '=')
        size++;
    var = ft_substr(value, 0, size);
    if (ft_strlen(var) > 1
        && (ft_isalpha(var[i]) == 0 && var[i] != '_'))
    {
        free(var);
        return (ERROR);
    }
    else if (ft_strlen(var) == 1 && var[i] == '_')
    {
        free(var);
        return (ERROR);
    }
    while (var[i] != '\0')
    {
        if (ft_isalnum(var[i]) == 0 && var[i] != '_' && var[i] != '=')
        {
            free(var);
            return (ERROR);
        }
        i++;
    }
    free(var);
    return (0);
}
