/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvaz-fe <igvaz-fe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 21:53:28 by igvaz-fe          #+#    #+#             */
/*   Updated: 2022/03/16 23:02:39 by igvaz-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int i)
{
	if (i >= 48 && i <= 57)
		return (1);
	else
		return (0);
}

static int	is_negative(const char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (str[i] != '\0' && !ft_isdigit(str[i]))
	{
		if (str[i] == '-')
			sign = -1;
		else if (str[i] == '+')
			sign = 1;
		i++;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	sign = is_negative(str);
	if (!str)
		return (0);
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

long	ft_atol(const char *str)
{
	long	value;
	long	i;
	long	sign;

	value = 0;
	i = 0;
	sign = (is_negative(str));
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	return (value * sign);
}
