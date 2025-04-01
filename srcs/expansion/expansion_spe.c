/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_spe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:14:55 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/01 15:07:16 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int specials_case(t_shell  *shell, char *current)
{
    if (current[1] == '?')
    {
        if (shell->utils.new_arg == NULL)
            shell->utils.new_arg = ft_strdup("le status");
        else
            shell->utils.new_arg = ft_strjoin(shell->utils.new_arg, "le status");
        return (VALID);
    }
    return (0);
}
