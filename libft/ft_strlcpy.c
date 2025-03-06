/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:08:10 by david_chell       #+#    #+#             */
/*   Updated: 2024/08/19 18:08:10 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, size_t l)
{
	size_t	i;

	i = 0;
	if (l == 0)
	{
		return (ft_strlen(src));
	}
	while (src[i] != '\0' && i < l -1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

// int main (void)
// {
// 	char source[] = "Les contours bien lazere";
// 	char destination[] = "";
// 	size_t l = 10; // copie jusqu a l - 1 pour le \0
// 	printf("AVANT : %s\n", destination);
// 	ft_strlcpy(destination, source, l);
// 	printf("APRES : %s\n", destination); 
// 	return (0);
// }
