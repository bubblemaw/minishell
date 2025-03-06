/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:18:36 by david_chell       #+#    #+#             */
/*   Updated: 2024/10/12 16:51:32 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}

// // remplace jusqu'a l les elements de void par c
// int main (void)
// {
// 	int	tab[5] = {1, 2, 3, 4, 5};
// 	int value = 0;
// 	int i = 0;

// 	printf("AVANT : ");
// 	while (i < 5) 
//         printf("[%d]", tab[i++]);
// 	i = 0;

//     // Remplissage du tableau avec memset
// 	ft_memset(tab, value, 16); // 8 pur remplacer 2 car un int vaut  4 octets

// 	printf("\nAPRES : ");
// 	i = 0;
// 	while (i < 5) 
//         printf("[%d]", tab[i++]);
// }
