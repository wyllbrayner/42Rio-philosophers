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

static void	ft_valid_input_amount(int argc, t_data *data);
static t_data	*ft_valid_input_character(char **argv, t_data *data);
static int	ft_valid_character(char *str);
static t_data	*ft_valid_input_number(char **argv, t_data *data);

t_data *ft_check_input(int argc, char **argv, t_data *data)
{
	data->ret = 0;
	ft_valid_input_amount(argc, data);
	if (data->ret < 0)
		return (data);
	ft_valid_input_character(argv, data);
	if (data->ret < 0)
		return (data);
	ft_valid_input_number(argv, data);
	return (data);
}

static void	ft_valid_input_amount(int argc, t_data *data)
{
	if (argc < 5 || argc > 6)
		data->ret = -1;
}

static t_data	*ft_valid_input_character(char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_valid_character(argv[i]) < 0)
		{
			data->ret = -2;
			return (data);
		}
		i++;
	}
	return (data);
}

static int	ft_valid_character(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (((str[i] == '-') || (str[i] == '+')) && (!str[i + 1]))
		return (-2);
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-2);
		i++;
	}
	return (TRUE);
}

static t_data	*ft_valid_input_number(char **argv, t_data *data)
{
	int		i;
	long	nbr;

	i = 1;
	while (argv[i])
	{
		nbr = ft_atol(argv[i]);
		if ((i == 1 && nbr <= 0) || (i <= 5 && nbr < 0) || (nbr > INT_MAX))
		{
			data->ret = -3;
			return (data);
		}
		i++;
	}
	return (data);
}