/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:09:38 by david_chell       #+#    #+#             */
/*   Updated: 2024/08/19 18:09:38 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	new;

	i = 0;
	signe = 1;
	new = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		new *= 10;
		new = new + (str[i] - '0');
		i++;
	}
	return (new * signe);
}

// int main (void)
// {
// 	const char test[] = " -230aa4";
// 	printf("faux : %d\n", ft_atoi(test));
// 	printf("vrai : %d\n", atoi(test));
// 	return (0);
// }
