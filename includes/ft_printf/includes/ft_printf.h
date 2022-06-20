/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:22:40 by mfreixo-          #+#    #+#             */
/*   Updated: 2022/06/20 11:22:42 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <limits.h>

int	ft_is_type(char c);
int	ft_putunsint(unsigned int nbr);
int	ft_putpointer(unsigned long long ptr);
int	ft_putx(unsigned int n, int fun);
int	ft_arg(char c, va_list ap);
int	ft_printf(const char *str, ...);
int	num_size(int n);
int	ft_putchar(char c);
int	ft_putstr(char *s);

#endif
