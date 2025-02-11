/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:07:43 by david_chell       #+#    #+#             */
/*   Updated: 2024/08/19 18:07:43 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *str1, char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && i < n)
	{
		if (str1[i] != str2[i])
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		i++;
	}
	if (i < n)
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}

// int main (void)
// {
// 	char test_1[] = "test";
// 	char test_2[] = "tesp";
// 	size_t n = 4;
// 	printf("%d\n", ft_strncmp(test_1, test_2, n));
// 	return (0);
// }
