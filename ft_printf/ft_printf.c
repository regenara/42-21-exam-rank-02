/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstoneho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:07:54 by mstoneho          #+#    #+#             */
/*   Updated: 2020/12/29 22:07:57 by mstoneho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   Assignment name  : ft_printf
**   Expected files   : ft_printf.c
**   Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
**   ---------------------------------------------------------------------------
**
**   Write a function named `ft_printf` that will mimic the real printf with
**   the following constraints:
**
**   - It will manage only the following conversions: s,d and x
**   - It will manage the minimum field width. (we will never test with a
**     field with of 0)
**   - It will manage only the precision flag `.`.
**
**   Your function must be declared as follows:
**
**   int ft_printf(const char *, ... );
**
**   Before you start we advise you to read the `man 3 printf` and
**   the `man va_arg`.
**   To test your program compare your results with the true printf.
**
**   Examples of the function output:
**
**   call: ft_printf("%10.2s\n", "toto");
**   out:        to$
**
**   call: ft_printf("Magic %s is %5d", "number", 42);
**   out:Magic number is    42%
**
**   call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
**   out:Hexadecimal for 42 is 2a$
*/

#include <unistd.h>
#include <stdarg.h>

#define ALL			"-0123456789sdx."
#define DIGITS		"-0123456789"

typedef struct	s_ft_printf
{
	int 	count;
	int 	width;
	int		precision;
	int 	point;
	int 	is_negative;

}				t_ft_printf;

void			ft_struct_fill(t_ft_printf *data, int count)
{
	data->count = count;
	data->width = 0;
	data->precision = 0;
	data->point = 0;
	data->is_negative = 0;
}

char			*ft_strchr(const char *s, int c)
{
	while (NULL != s && *s)
	{
		if (*(char*)s++ == c)
			return ((char*)--s);
	}
	return (c == '\0' ? (char*)s : NULL);
}

int 			ft_strlen(char *str)
{
	int 	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int 			ft_nbrlen(unsigned int n, unsigned int numsys)
{
	if (n < numsys)
		return (1);
	return (1 + ft_nbrlen(n / numsys, numsys));
}

long int 		ft_atoi(char *text)
{
	int			p;
	long int	n;

	n = 0;
	p = 1;
	while ((*text <= 13 && *text >= 9) || *text == 32)
		text++;
	if (*text == '-' || *text == '+')
	{
		if (*text == '-')
			p = -1;
		text++;
	}
	while ('0' <= *text && *text <= '9')
	{
		n = n * 10 + (*text - 48);
		text++;
	}
	return (n * p);
}

int				ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int 			ft_putstr(char *str, int len)
{
	int		i;

	i = 0;
	while (*str && len > 0)
	{
		i += ft_putchar(*str);
		str++;
		len--;
	}
	return (i);
}

int				ft_putnbr(unsigned int n)
{
	char	d;
	int		i;

	i = 1;
	d = n % 10 + '0';
	if (n >= 10)
		i += ft_putnbr(n / 10);
	ft_putchar(d);
	return (i);
}

void			ft_puthex(t_ft_printf *data, unsigned long long int nbr,
				  unsigned long long int nbrcpy)
{
	unsigned int	mod;
	char			*base;

	base = "0123456789abcdef";
	if (nbr >= 10)
	{
		mod = nbr % 16;
		nbr /= 16;
		ft_puthex(data, nbr, nbrcpy);
		ft_putchar(base[mod]);
		data->count++;
	}
	else if (nbr > 0 || !nbrcpy)
	{
		ft_putchar(base[nbr]);
		data->count++;
	}
}

void 			ft_print_s(t_ft_printf *data, va_list argptr)
{
	char	*str;
	int 	len;

	str = va_arg(argptr, char *);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (len > data->precision && data->point)
		len = data->precision;
	data->width = data->width - len;
	while (data->width-- > 0)
		data->count += ft_putchar(' ');
	data->count += ft_putstr(str, len);
}

unsigned int 	ft_get_nbr(t_ft_printf *data, va_list argptr, char type)
{
	unsigned int nbr;

	if (type == 'd')
	{
		long int n = va_arg(argptr, int);
		if (n < 0)
		{
			n = -n;
			data->is_negative = 1;
		}
		nbr = n;
	}
	else
		nbr = va_arg(argptr, unsigned int);
	return (nbr);
}

void			ft_print_d(t_ft_printf *data, va_list argptr, char type)
{
	long int		nbr;
	int				len;

	nbr = ft_get_nbr(data, argptr, type);
	if (type == 'd')
		len = ft_nbrlen(nbr, 10);
	else
		len = ft_nbrlen(nbr, 16);
	if (!nbr && !data->precision && data->point)
	{
		while (data->width-- > 0)
			data->count += ft_putchar(' ');
	}
	else
	{
		if (data->width > data->precision && data->precision < len)
			data->width = data->width - len;
		else
			data->width = data->width - data->precision;
		if (data->is_negative)
			data->width--;
		while (data->width-- > 0)
			data->count += ft_putchar(' ');
		if (data->is_negative)
			data->count += ft_putchar('-');
		if (type == 'd')
			data->count += ft_putnbr(nbr);
		else
			ft_puthex(data, nbr, nbr);
	}
}

char 			*ft_parser(t_ft_printf *data, char *text, va_list argptr)
{
	if (ft_strchr(DIGITS, *text))
	{
		data->width = ft_atoi(text);
		while (ft_strchr(DIGITS, *text))
			text++;
	}
	if (*text == '.')
	{
		text++;
		data->point = 1;
		data->precision = ft_atoi(text);
		while (ft_strchr(DIGITS, *text))
			text++;
	}
	if (data->width < 0)
		data->width = -data->width;
	if (*text == 's')
		ft_print_s(data, argptr);
	else if (*text == 'd' || *text == 'x')
		ft_print_d(data, argptr, *text);
	ft_struct_fill(data, data->count);
	return (text);
}

int				ft_printf(const char *text, ... )
{
	va_list		argptr;
	t_ft_printf	data;

	va_start(argptr, text);
	ft_struct_fill(&data, 0);
	while (*text)
	{
		if (*text == '%' && ft_strchr(ALL, *(text + 1)))
			text = ft_parser(&data, (char *)++text, argptr);
		else
			data.count += ft_putchar(*text);
		text++;
	}
	va_end(argptr);
	return (data.count);
}
