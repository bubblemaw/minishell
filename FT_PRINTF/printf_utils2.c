/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:08:13 by maw               #+#    #+#             */
/*   Updated: 2024/12/16 13:32:34 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_fi(int n, int fd)
{
	int			modulo;
	char		reste;
	int			count;

	count = 0;
	if (n == -2147483648)
	{
		count += write(fd, "-2147483648", 11);
		return (count);
	}
	if (n < 0)
	{
		count += write(fd, "-", 1);
		n *= -1;
	}
	if (n >= 10)
	{
		modulo = n % 10;
		reste = modulo + '0';
		count += ft_putnbr_fi(n / 10, fd);
	}
	if (n < 10)
		reste = n + '0';
	count += write(fd, &reste, 1);
	return (count);
}

int	ft_putstr(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (s == NULL)
	{
		count += write(1, "(null)", 6);
		return (count);
	}
	while (s[i])
	{
		count += write(1, &s[i], 1);
		i++;
	}
	return (count);
}

int	ft_putchar_spe(unsigned char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (1);
}
