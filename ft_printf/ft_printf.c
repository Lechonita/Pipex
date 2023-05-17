/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:11:26 by jrouillo          #+#    #+#             */
/*   Updated: 2023/04/04 16:33:11 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_treat_format(va_list args, const char format)
{
	int		count;

	count = 0;
	if (format == 'c')
		count += ft_print_char(va_arg(args, int));
	else if (format == 's')
		count += ft_print_str(va_arg(args, char *));
	else if (format == 'p')
		count += ft_count_ptr(va_arg(args, uintptr_t));
	else if (format == 'd' || format == 'i')
		count += ft_print_int(va_arg(args, int));
	else if (format == 'u')
		count += ft_print_unsignedint(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		count += ft_print_hexa(va_arg(args, unsigned int), format);
	else if (format == '%')
		count += ft_print_char(format);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			count;
	int			i;

	if (!format || !*format)
		return (0);
	count = 0;
	i = -1;
	va_start(args, format);
	while (format[++i])
	{
		if (format[i] == '%')
			count += ft_treat_format(args, format[i++ + 1]);
		else
			count += ft_print_char(format[i]);
	}
	va_end(args);
	return (count);
}
