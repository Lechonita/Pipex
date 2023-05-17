/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:17:07 by jrouillo          #+#    #+#             */
/*   Updated: 2023/04/04 16:32:40 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(char *format)
{
	int	count;

	count = -1;
	if (!format)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (format[++count])
		write(1, &format[count], 1);
	return (count);
}
