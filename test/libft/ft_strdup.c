/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:08:47 by david_chell       #+#    #+#             */
/*   Updated: 2024/08/19 18:08:47 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	new = (char *)malloc(sizeof(char) * i +1);
	if (new == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (str[i] != '\0')
	{
		new[i] = str[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

// int main(void)
// {
// 	char line[] = "Ekipafon";
// 	printf("%s\n", ft_strdup(line));
// 	return (0);
// }
