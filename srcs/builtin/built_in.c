/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:34:33 by maw               #+#    #+#             */
/*   Updated: 2025/03/26 11:22:12 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_in(t_cmd *cmd, t_shell *shell)
{
	if (ft_strlen(cmd->arg[0]) == 4 && ft_strncmp(cmd->arg[0], "echo", 4) == 0)
		return (echo(cmd));
	else if (ft_strlen(cmd->arg[0]) == 6 && ft_strncmp(cmd->arg[0], "export", 6) == 0)
	{
		export(cmd, shell);
		return (VALID);
	}
	else if(ft_strlen(cmd->arg[0]) >= 2 && ft_strncmp(cmd->arg[0], "cd", 2) == 0)
		return (cd(cmd, shell));
	else if(ft_strlen(cmd->arg[0]) >= 3 && ft_strncmp(cmd->arg[0], "env", 3) == 0)
		return (ft_env(cmd, shell));
	else if(ft_strlen(cmd->arg[0]) >= 3 && ft_strncmp(cmd->arg[0], "pwd", 3) == 0)
		return(pwd());
	else if(ft_strlen(cmd->arg[0]) >= 5 && ft_strncmp(cmd->arg[0], "unset", 5) == 0)
		return(unset(cmd, shell));
	else if(ft_strlen(cmd->arg[0]) >= 4 && ft_strncmp(cmd->arg[0], "exit", 4) == 0)
	{
		ft_exit(cmd, shell);
		return (VALID);
	}
	return (ERROR);	
}
