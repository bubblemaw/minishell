/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:34:33 by maw               #+#    #+#             */
/*   Updated: 2025/03/10 14:07:35 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_in(t_cmd *cmd)
{
	if(ft_strlen(cmd->arg[0]) >= 4 && ft_strncmp(cmd->arg[0], "echo", 4) == 0)
	{
		echo(cmd);
		return (VALID);
	}
	return (ERROR);	
}
