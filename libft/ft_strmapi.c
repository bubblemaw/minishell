/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:47:37 by david_chell       #+#    #+#             */
/*   Updated: 2024/10/12 14:52:01 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new;

	i = 0;
	new = ft_strdup(s);
	if (new == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}

// char big_maj(unsigned int nb, char c)
// {
// 	nb = 1; // juste pour l'utilier
// 	if (c >= 'a' && c <= 'z')
// 		return (c - 32); // Transforme en majuscule
// 	return (c);
// }
//  permet de faire agir une fonction sur le pointeur de s
// int main(void)
// {
// 	const char line[] = "Le sprite est rose comme Buu petit";
// 	printf("%s\n", ft_strmapi(line, big_maj));
// 	return (0);
// }