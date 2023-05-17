/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:17:11 by jrouillo          #+#    #+#             */
/*   Updated: 2023/04/04 16:33:06 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hexa(unsigned int nb, const char format)
{
	char	*base;
	char	str[20];
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nb == 0)
		count += ft_print_int(0);
	while (nb)
	{
		str[i] = base[nb % 16];
		nb = nb / 16;
		i++;
	}
	while (i--)
	{
		ft_putchar(str[i]);
		count++;
	}
	return (count);
}

int	ft_len_ptr(uintptr_t ptr)
{
	int	len;

	len = 0;
	while (ptr)
	{
		ptr /= 16;
		len++;
	}
	return (len);
}

void	ft_print_ptr(uintptr_t ptr)
{
	char		*base;
	char		str[25];
	int			i;

	base = "0123456789abcdef";
	i = 0;
	write(1, "0x", 2);
	while (ptr)
	{
		str[i] = base[ptr % 16];
		ptr /= 16;
		i++;
	}
	while (i--)
		ft_putchar(str[i]);
}

int	ft_count_ptr(uintptr_t ptr)
{
	int		count;

	count = 0;
	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		count = 5;
	}
	else
	{
		ft_print_ptr(ptr);
		count = ft_len_ptr(ptr) + 2;
	}
	return (count);
}
