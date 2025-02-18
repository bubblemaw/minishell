/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:09:30 by david_chell       #+#    #+#             */
/*   Updated: 2024/08/19 18:09:30 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(char car)
{
	if ((car >= 'a' && car <= 'z') || (car >= 'A' && car <= 'Z')
		|| (car >= '0' && car <= '9'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/*
int main (void)
{
	char test = 'T';
	printf ("%d\n", ft_isalnum(test));    
	return (0);
}
*/