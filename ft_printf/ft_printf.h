/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:11:32 by jrouillo          #+#    #+#             */
/*   Updated: 2023/04/04 16:33:13 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

	/* FT_PRINTF */

int			ft_treat_format(va_list args, const char format);
int			ft_printf(const char *format, ...);

	/* FT_PRINTF_CHAR */

int			ft_print_char(char c);
int			ft_print_str(char *format);

	/* FT_PRINTF_INT_UNSIGNED */

void		ft_putchar(char c);
int			ft_len_int(long nb);
int			ft_print_int(int nb);
int			ft_print_unsignedint(unsigned int nb);

	/* FT_PRINT_HEXA_PTR */

int			ft_print_hexa(unsigned int nb, const char format);
int			ft_len_ptr(uintptr_t ptr);
void		ft_print_ptr(uintptr_t ptr);
int			ft_count_ptr(uintptr_t ptr);

#endif