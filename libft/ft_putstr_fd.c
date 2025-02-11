/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:09:45 by david_chell       #+#    #+#             */
/*   Updated: 2024/10/12 16:26:32 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	return ;
}

// int main (void)
// {
// 	char line[] = "Bonjour tout le monde";
// 	int fd;
// 	ft_putstr_fd(line, fd);
// 	printf("\n");
// 	return (0);
// }