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

#include "../header/ft_philosopher.h"

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
		return (TRUE);
	return (FALSE);
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

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
