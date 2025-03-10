/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:21:32 by maw               #+#    #+#             */
/*   Updated: 2025/03/10 14:08:58 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;
	size_t copy_size;

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