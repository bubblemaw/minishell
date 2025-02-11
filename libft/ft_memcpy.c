/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:14:30 by david_chell       #+#    #+#             */
/*   Updated: 2024/10/12 17:39:21 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
	{
		return (dest);
	}
	while (i < len)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

// // pareil que strcpy mais on choisit le type que on veut mettre
// int main (void)
// {
// 	char src[] = "le bruit des vagues me permet";
// 	char dst[100] = "";
// 	size_t n = 8;
// 	printf("dest AVANT : %s\n", dst);
// 	ft_memcpy(dst, src, n);
// 	printf("dest APRES : %s\n", dst);
// 	return (0);
// }
