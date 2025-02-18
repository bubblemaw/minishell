/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:42:13 by david_chell       #+#    #+#             */
/*   Updated: 2024/10/12 17:02:12 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_nb(int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
	{
		nb *= -1;
		i++;
	}
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nb)
{
	int		i;
	char	*new;

	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	if (nb == 0)
		return (ft_strdup("0"));
	i = count_nb(nb);
	new = (char *) malloc(sizeof(char) * (i + 1));
	if (new == NULL)
		return (NULL);
	new[i] = '\0';
	i--;
	if (nb < 0)
	{
		nb *= -1;
		new[0] = '-';
	}
	while (nb > 0)
	{
		new[i] = (nb % 10) + '0';
		nb /= 10;
		i--;
	}
	return (new);
}

// int main (void)
// {
//     int test = -2147483648;
//     printf("%s\n", ft_itoa(test));
//     return (0);
// }