/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david_chellen <david_chellen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:09:25 by david_chell       #+#    #+#             */
/*   Updated: 2024/08/19 18:09:25 by david_chell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int lettre)
{
	if ((lettre >= 'a' && lettre <= 'z') || (lettre >= 'A' && lettre <= 'Z'))
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
	char lettre = '/';
	printf("%d\n", ft_isalpha(lettre));
	return (0);
}
*/