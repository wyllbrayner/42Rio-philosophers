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

/*
int	ft_isdigit(int c) // NAO
{
	return ((c >= '0') && (c <= '9'));
}
*/

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

void	ft_error(t_data *data)
{
	if (data->ret == -1)
		printf("Error: Invalid number of arguments.\n");
	else if ((data->ret == -2) || (data->ret == -3))
		printf("Error: Invalid arguments.\n");
	else if ((data->ret == -4) || (data->ret == -5))
		printf("Error: Unable to initialize structures.\n");
	else if (data->ret == -6)
		printf("Error: It was not possible to create all threads.\n");
	else if (data->ret == -7)
		printf("Error: It was not possible to group all threads.\n");
}