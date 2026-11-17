/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_fake.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:43:12 by maw               #+#    #+#             */
/*   Updated: 2025/04/21 16:30:30 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_direction_fake(t_cmd *cmd)
{
	int	infd;

	if (cmd->infile != NULL)
	{
		infd = open (cmd->infile, O_RDONLY);
		if (infd == -1)
		{
			close(infd);
			return (0);
		}
	}
	if (outfile_direction_fake(cmd) == 0)
		return (0);
	return (1);
}

int	outfile_direction_fake(t_cmd *cmd)
{
	int	outfd;

	if (cmd->append == 1)
	{
		outfd = open (cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfd == -1)
		{
			close(outfd);
			return (0);
		}
	}
	else if (cmd->outfile != NULL)
	{
		outfd = open (cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfd == -1)
		{
			close(outfd);
			return (0);
		}
	}
	return (1);
}

int	ft_test_direction(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->infile || current->outfile)
		{
			if (ft_direction_fake(current) == 0)
			{
				while (current->next)
				{
					if (current->type == PIPE)
						break ;
					current = current->next;
					current->valid = ERROR;
				}
			}
		}
		current = current->next;
	}
	return (VALID);
}
