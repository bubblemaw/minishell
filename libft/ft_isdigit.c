/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:09:08 by david_chell       #+#    #+#             */
/*   Updated: 2024/08/19 18:09:08 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int nbr)
{
	if (nbr >= '0' && nbr <= '9')
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
    int i = '0';
    while (i <= '9')
    {
        printf("%d", ft_isdigit(i));
        i++;
    }
}
*/