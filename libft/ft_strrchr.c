/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:07:34 by david_chell       #+#    #+#             */
/*   Updated: 2024/08/19 18:07:34 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	while (i >= 0)
	{
		if (str[i] == (char) c)
		{
			return (&str[i]);
		}
		i--;
	}
	return (NULL);
}

// // comme strch sauf que on part depuis la fin
// int main (void)
// {
// 	char string[] = "Le sabre rouge";
// 	char car = 'r';
// 	printf("AVANT : %s\n", string);
// 	printf("APRES : %s\n", ft_strrchr(string, car));
// 	return (0);
// }