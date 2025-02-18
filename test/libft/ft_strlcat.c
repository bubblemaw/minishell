/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:08:24 by david_chell       #+#    #+#             */
/*   Updated: 2024/08/19 18:08:24 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t dstsize)
{
	size_t	full_size;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	full_size = ft_strlen(dest) + ft_strlen(src);
	if (dstsize < ft_strlen(dest))
		return (ft_strlen(src) + dstsize);
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && i + 1 < dstsize)
	{
		dest [i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (full_size);
}

// // concatenation sécurisée car on la fait jusqu'à l donc avec la
// // valeur qui est return on sait que si elle < 
// // que la full size alors ca marche pas

// int main (void)
// {
// 	char phrase_1[100] = "le tapper a Tyrese";
// 	char phrase_2[] = " et les contours a Beligham";
// 	size_t l = 18; // longueur qu on autorise a concatener 
// 				   // donc 18 pour que ca marche
// 	printf("%zu\n", ft_strlcat(phrase_1, phrase_2, l));
// 	return (0);
// }
