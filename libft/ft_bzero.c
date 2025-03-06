/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:55:32 by david_chell       #+#    #+#             */
/*   Updated: 2024/10/12 14:05:08 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
	{
		return ;
	}
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
	return ;
}

// int main (void)
// {
// 	char a[] = "Ekip";
// 	size_t n = 1;
// 	printf("%s\n", a);
// 	ft_bzero(a, n);
// 	printf("%s\n", a);
// 	return (0);
// }
