/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:14:54 by david_chell       #+#    #+#             */
/*   Updated: 2024/10/12 17:27:03 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int val, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (((unsigned char *)ptr)[i] == ((unsigned char)val))
		{
			return (((unsigned char *)ptr) + i);
		}
		i++;
	}
	return (NULL);
}

// // comme strchr mais cette fois on peut mettre le type qu on veut comme
// // dans l'exemple avec le tableau de int
// int main (void)
// {
// 	int tab[5] = {1, 2, 3, 4, 5};
// 	int val = 3;
// 	size_t len = 16;
// 	ft_memset(tab, val, len);

// 	for (int i = 0; i < 5; i++)
//         printf("[%d]", tab[i]); 
// 	return (0);
// }
