/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int_unsigned.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:17:14 by jrouillo          #+#    #+#             */
/*   Updated: 2023/04/04 16:33:09 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_len_int(long nb)
{
	int	len;

	len = 0;
	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	if (nb == 0)
		len = 1;
	else
	{
		while (nb)
		{
			nb /= 10;
			len++;
		}
	}
	return (len);
}

int	ft_print_int(int nb)
{
	int				count;
	unsigned int	i;

	count = 0;
	if (nb < 0)
	{
		ft_putchar('-');
		i = -nb;
		count += 1;
	}
	else
		i = nb;
	if (i > 9)
	{
		ft_print_int(i / 10);
		ft_print_int(i % 10);
		count += ft_len_int(i);
	}
	else
	{
		ft_putchar(i + '0');
		count += 1;
	}
	return (count);
}

int	ft_print_unsignedint(unsigned int nb)
{
	int		count;

	count = 0;
	if (nb > 9)
	{
		ft_print_int(nb / 10);
		ft_print_int(nb % 10);
		count += ft_len_int(nb);
	}
	else
	{
		ft_putchar(nb + '0');
		count++;
	}
	return (count);
}
