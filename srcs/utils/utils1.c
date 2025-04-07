/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:21:32 by maw               #+#    #+#             */
/*   Updated: 2025/04/07 20:52:31 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free (ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return malloc(new_size);
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		free (ptr);
		return (NULL);
	}
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;	
	new_ptr = ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	ptr = NULL;
	return (new_ptr);
}

void	init_shell(t_shell *shell)
{
	shell->crash.prev = NULL;
	shell->crash.new_var = NULL;
	shell->crash.tmp = NULL;
	shell->creat.content = NULL;
	shell->creat.first = NULL;
	shell->exp.new = NULL;
	shell->exp.sub_env = NULL;
	shell->exp.tmp = NULL;
	shell->exp.tmp_2 = NULL;
	shell->exp.tmp_3 = NULL;
	shell->exp.add = NULL;
	shell->exp.line = NULL;
	shell->exp.tab = NULL;
	shell->exp.temp = NULL;
	shell->kill.new = NULL;
	shell->kill.tmp = NULL;
	shell->kill.stash = NULL;
	return ;
}
