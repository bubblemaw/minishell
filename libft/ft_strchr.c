/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:08:54 by david_chell       #+#    #+#             */
/*   Updated: 2024/08/19 18:08:54 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
		{
			return (str + i);
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return (str + i);
	}
	return (NULL);
}

// return un pointeur vers la premiere occurence de c dans str
// si la fonction ne trouve pas c return null
// int main (void)
// {
// 	char string[] = "Le sabre rouge";
// 	char car = 's';
// 	printf("AVANT : %s\n", string);
// 	printf("APRES : %s\n", ft_strchr(string, car));
// 	return (0);
// }
