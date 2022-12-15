/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/08/17 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cc ft_testes.c -Wall -Werror -Wextra -pthread -o test && ./test

#include "../header/ft_philosopher.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd > 0 && *s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char c;
	if (fd > 0)
	{
		if (n == -2147483648)
		{
			write(fd, "-2", 2);
			n = 147483648;
		}
		else if (n < 0)
		{
			write(fd, "-", 1);
			n *= -1;
		}
		if (n / 10)
			ft_putnbr_fd((n / 10), fd);
		c = ((n % 10) + '0');
		write(fd, &c, 1);
	}
}

int	ft_isspace(int c)
{
	unsigned char	chr;

	chr = (unsigned char)c;
	if ((chr >= 9 && chr <= 13) || (chr == 32))
		return (TRUE);
	return (FALSE);
}

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

long	ft_atol(char *str)
{
	int		i;
	int		signal;
	long	nbr;

	i = 0;
	signal = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
	nbr = 0;
	while (ft_isdigit(str[i]))
	{
		nbr = (10 * nbr) + (str[i] - '0');
		i++;
	}
	return (signal * nbr);
}
