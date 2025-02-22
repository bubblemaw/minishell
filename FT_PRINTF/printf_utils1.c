/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:06:02 by maw               #+#    #+#             */
/*   Updated: 2025/02/14 22:47:32 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_unsigned(unsigned int n, int fd)
{
	int		modulo;
	char	reste;
	int		count;

	count = 0;
	if (n >= 10)
	{
		modulo = n % 10;
		reste = modulo + '0';
		count += ft_putnbr_unsigned(n / 10, fd);
		if (write(fd, &reste, 1) == -1)
			return (-1);
		count++;
	}
	if (n < 10)
	{
		reste = n + '0';
		if (write(fd, &reste, 1) == -1)
			return (-1);
		count++;
	}
	return (count);
}

int	ft_puthexa_fd(unsigned int num, int fd)
{
	char			reste;
	int				count;

	count = 0;
	if (num >= 16)
	{
		count += ft_puthexa_fd(num / 16, fd);
		num = num % 16;
	}
	if (num < 10)
	{
		reste = num + '0';
	}
	if (num >= 10 && num < 16)
		reste = (num - 10) + 'a';
	count += write(fd, &reste, 1);
	return (count);
}

int	ft_puthexa_pre(unsigned long int n, int fd)
{
	char	reste;
	int		count;

	count = 0;
	if (n >= 16)
	{
		count += ft_puthexa_pre(n / 16, fd);
		n = n % 16;
	}
	if (n < 10)
	{
		reste = n + '0';
	}
	if (n >= 10 && n < 16)
		reste = (n - 10) + 'a';
	count += write(fd, &reste, 1);
	return (count);
}

int	put0x(void *ptr)
{
	int	count;
	int	result;

	result = 0;
	count = 0;
	count += write(1, "0x", 2);
	if (count < 0)
		return (-1);
	result = ft_puthexa_pre((unsigned long int)ptr, 1);
	if (result == -1)
		return (-1);
	count += result;
	return (count);
}

int	ft_puthexa_up_fd(unsigned int n, int fd)
{
	char	reste;
	int		count;

	count = 0;
	if (n >= 16)
	{
		count += ft_puthexa_up_fd(n / 16, fd);
		n = n % 16;
	}
	if (n < 10)
	{
		reste = n + '0';
	}
	if (n >= 10 && n < 16)
		reste = (n - 10) + 'A';
	count += write(fd, &reste, 1);
	return (count);
}
