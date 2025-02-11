/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:47:20 by david_chell       #+#    #+#             */
/*   Updated: 2024/10/12 17:56:14 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (((char *)dest) < ((char *)src))
	{
		while (i < len)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	else
	{
		while (len > 0)
		{
			len--;
			((char *)dest)[len] = ((char *)src)[len];
		}
	}
	return (dest);
}

// int main (void)
// {
//     char destination[] = "Un bon poulet yassa";
//     char source[] = "poulet";
//     size_t taille = 6; // le nombre d'octets qu on veut copier de source
// 	// pour changer l'emplacement de la source il faut juste mettre + x
// 	// a la dest dans l appel de la fonction
//     ft_memmove(destination + 7, source, taille);
//     printf("%s\n", destination);
//     return (0);
// }