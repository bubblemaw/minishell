/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:07:51 by david_chell       #+#    #+#             */
/*   Updated: 2024/08/19 18:07:51 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str_1, const char *str_2, size_t n)
{
	size_t	i;
	size_t	j;

	if (str_2[0] == '\0')
	{
		return ((char *)str_1);
	}
	i = 0;
	while (str_1[i] != '\0' && i < n)
	{
		j = 0;
		while (str_2[j] == str_1[i + j] && (i + j) < n)
		{
			if (str_2[j + 1] == '\0')
				return ((char *)str_1 + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

// int main (void)
// {
// 	const char test_1[] = "le sabre rouge de vador";
// 	const char test_2[] = "le";
// 	size_t n = 2;
// 	printf("%s\n", ft_strnstr(test_1, test_2, n));
// 	return (0);
// }
