/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:09:20 by david_chell       #+#    #+#             */
/*   Updated: 2024/08/19 18:09:20 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int car)
{
	if (car >= 0 && car <= 127)
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
    int i = 123;
    while (i <= 127)
    {
        printf("%d", ft_isascii(i));
        i++;
    }
}
*/