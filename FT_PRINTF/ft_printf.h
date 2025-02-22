/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:45:26 by maw               #+#    #+#             */
/*   Updated: 2024/12/16 13:32:38 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "LIBFT/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_putnbr_fi(int n, int fd);
int		ft_puthexa_fd(unsigned int n, int fd);
int		ft_puthexa_up_fd(unsigned int n, int fd);
int		ft_putnbr_unsigned(unsigned int n, int fd);
int		put0x(void *ptr);
int		ft_puthexa_pre(unsigned long int n, int fd);
int		ft_putstr(char *s);
int		ft_printf(const char *format, ...);
int		ft_putchar_spe(unsigned char c, int fd);

#endif
