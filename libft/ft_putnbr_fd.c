/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:10:37 by david_chell       #+#    #+#             */
/*   Updated: 2024/10/12 16:26:35 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		n %= 10;
	}
	if (n <= 9)
	{
		n = n + 48;
		write(fd, &n, 1);
	}
	return ;
}

// int main (void)
// {
//     int fd;
//     int nombre = -2147483648;
//     ft_putnbr_fd(nombre, fd);
//     printf("\n");
//     return (0);
// }