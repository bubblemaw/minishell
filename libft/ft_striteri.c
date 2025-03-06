/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:42:32 by david_chell       #+#    #+#             */
/*   Updated: 2024/10/12 15:55:56 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
	return ;
}

// void big_maj(unsigned int i, char *c) 
// {
//     if (*c >= 'a' && *c <= 'z') 
// 	{
// 		*c -= 32;
//     }
//     return ;
// }
// // comme mapi mais la fonction prends un string et pas un char
// int main (void)
// {
//     char line[] = "Le sprite est rose comme Buu petit";
// 	ft_striteri(line, big_maj);
//     printf("%s\n", line);
//     return (0);
// }
