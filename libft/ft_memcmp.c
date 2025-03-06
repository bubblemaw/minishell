/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:40:11 by david_chell       #+#    #+#             */
/*   Updated: 2024/10/22 13:08:44 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[j])
		{
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[j]);
		}
		i++;
		j++;
	}
	return (0);
}

// // pareil que strncmp mais on peut choisir le type de variables
// int main (void)
// {
// 	char *str1 = "abcde";
// 	char *str2 = "abcde";
// 	size_t taille = 3;
// 	printf("%d\n", ft_memcmp(str1, str2, taille));
// 	return (0);
// }
