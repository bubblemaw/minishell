/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:44:34 by david_chell       #+#    #+#             */
/*   Updated: 2024/10/12 16:58:46 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	tot_size;
	void	*ptr;

	i = 0;
	tot_size = nmemb * size;
	ptr = malloc(tot_size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	while (i < tot_size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

// // comme malloc mais ca met toutes les valeurs a 0 une fois
// // que l'on a alloué la memoire
// int main (void)
// {
//     char *test;
//     size_t nb = 10;
//     size_t taille = 1;
//     size_t i = 0;
//     test = (char *)ft_calloc(nb, taille);
//     if (test == NULL)
//         return (0);
//     for (i = 0; i < nb; i++)
//         printf("test[%zu] = %d\n", i, (unsigned char)test[i]);
//     return (0);
// }