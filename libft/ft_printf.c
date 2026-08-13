/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:38:38 by hoigag            #+#    #+#             */
/*   Updated: 2026/08/13 18:00:35 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putlnbr(long long nb, int *counter)
{
	if (nb < 0)
	{
		ft_putchar('-', counter);
		nb = -nb;
	}
	if (nb > 9)
		ft_putlnbr(nb / 10, counter);
	ft_putchar(nb % 10 + 48, counter);
}

static void	ft_print_format(va_list *ap, char mod, char c, int *counter, int prec)
{
	char	*s;
	int		i;

	if (c == '%')
		ft_putchar(c, counter);
	else if (c == 'c')
		ft_putchar(va_arg(*ap, int), counter);
	else if (c == 's')
	{
		s = va_arg(*ap, char *);
		i = 0;
		while (s && s[i] && (prec < 0 || i < prec))
			ft_putchar(s[i++], counter);
	}
	else if ((c == 'd' || c == 'i') && mod == 'l')
		ft_putlnbr(va_arg(*ap, long long), counter);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(*ap, int), counter);
	else if (c == 'x')
		ft_puthex(va_arg(*ap, unsigned int), 0, counter);
	else if (c == 'X')
		ft_puthex(va_arg(*ap, unsigned int), 1, counter);
	else if (c == 'u')
		ft_putunbr(va_arg(*ap, unsigned int), counter);
	else if (c == 'p')
	{
		ft_putstr("0x", counter);
		ft_puthex_long(va_arg(*ap, unsigned long), 0, counter);
	}
	else
		ft_putchar(c, counter);
}

int	ft_printf(const char *s, ...)
{
	int		counter;
	int		i;
	int		prec;
	char	mod;
	va_list	ap;

	counter = 0;
	i = 0;
	va_start(ap, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			mod = '\0';
			prec = -1;
			if (s[i] == 'l')
			{
				mod = 'l';
				i++;
				if (s[i] == 'l')
					i++;
			}
			if (s[i] == '.')
			{
				i++;
				prec = ft_atoi(s + i);
				while (s[i] && (s[i] >= '0' && s[i] <= '9'))
					i++;
			}
			if (s[i])
				ft_print_format(&ap, mod, s[i], &counter, prec);
			else
				break ;
		}
		else
			ft_putchar(s[i], &counter);
		i++;
	}
	va_end(ap);
	return (counter);
}
