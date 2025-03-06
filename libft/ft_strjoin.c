/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:08:33 by david_chell       #+#    #+#             */
/*   Updated: 2024/08/19 18:08:33 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *str_1, char *str_2)
{
	char	*new;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(str_1) + ft_strlen(str_2);
	new = (char *)malloc(sizeof(char) * size + 1);
	i = 0;
	j = 0;
	if (new == NULL)
		return (NULL);
	while (str_1[i] != '\0')
	{
		new[i] = str_1[i];
		i++;
	}
	while (str_2[j] != '\0')
	{
		new[i] = str_2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

// // copie et concatè les 2 chaines de char dans une seule nouvelle
// int main (void)
// {
// 	char s1[] = "la tapper a Haliburton";
// 	char s2[] = " et les contours a Belligham";
// 	printf("%s\n", ft_strjoin(s1, s2));
// 	return (0);
// }
