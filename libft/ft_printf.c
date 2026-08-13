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

static void	ft_print_str(va_list *ap, int prec, int *counter)
{
	char	*s;
	int		i;

	s = va_arg(*ap, char *);
	i = 0;
	while (s && s[i] && (prec < 0 || i < prec))
		ft_putchar(s[i++], counter);
}

static void	ft_print_format(va_list *ap, t_fmt f, int *counter)
{
	if (f.c == 'c')
		ft_putchar(va_arg(*ap, int), counter);
	else if (f.c == 's')
		ft_print_str(ap, f.prec, counter);
	else if ((f.c == 'd' || f.c == 'i') && f.mod == 'l')
		ft_putlnbr(va_arg(*ap, long long), counter);
	else if (f.c == 'd' || f.c == 'i')
		ft_putnbr(va_arg(*ap, int), counter);
	else if (f.c == 'x')
		ft_puthex(va_arg(*ap, unsigned int), 0, counter);
	else if (f.c == 'X')
		ft_puthex(va_arg(*ap, unsigned int), 1, counter);
	else if (f.c == 'u')
		ft_putunbr(va_arg(*ap, unsigned int), counter);
	else if (f.c == 'p')
	{
		ft_putstr("0x", counter);
		ft_puthex_long(va_arg(*ap, unsigned long), 0, counter);
	}
	else
		ft_putchar(f.c, counter);
}

static int	ft_parse_spec(const char *s, int i, t_fmt *f)
{
	f->mod = '\0';
	f->prec = -1;
	if (s[i] == 'l')
	{
		f->mod = 'l';
		i++;
		if (s[i] == 'l')
			i++;
	}
	if (s[i] == '.')
	{
		i++;
		f->prec = ft_atoi(s + i);
		while (s[i] >= '0' && s[i] <= '9')
			i++;
	}
	f->c = s[i];
	return (i);
}

int	ft_printf(const char *s, ...)
{
	int		counter;
	int		i;
	t_fmt	f;
	va_list	ap;

	counter = 0;
	i = 0;
	va_start(ap, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i = ft_parse_spec(s, i + 1, &f);
			if (!f.c)
				break ;
			ft_print_format(&ap, f, &counter);
		}
		else
			ft_putchar(s[i], &counter);
		i++;
	}
	va_end(ap);
	return (counter);
}
