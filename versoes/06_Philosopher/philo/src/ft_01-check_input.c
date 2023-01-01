/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_01-check_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/12/30 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_philosopher.h"

static void		ft_valid_input_amount(int argc, t_data *dt);
static t_data	*ft_valid_input_character(char **argv, t_data *dt);
static int		ft_valid_character(char *str);
static t_data	*ft_valid_input_number(char **argv, t_data *dt);

t_data	*ft_check_input(int argc, char **argv, t_data *dt)
{
	dt->ret = 0;
	ft_valid_input_amount(argc, dt);
	if (dt->ret < 0)
		return (dt);
	ft_valid_input_character(argv, dt);
	if (dt->ret < 0)
		return (dt);
	ft_valid_input_number(argv, dt);
	return (dt);
}

static void	ft_valid_input_amount(int argc, t_data *dt)
{
	if (argc < 5 || argc > 6)
		dt->ret = -1;
}

static t_data	*ft_valid_input_character(char **argv, t_data *dt)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_valid_character(argv[i]) < 0)
		{
			dt->ret = -2;
			return (dt);
		}
		i++;
	}
	return (dt);
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

static t_data	*ft_valid_input_number(char **argv, t_data *dt)
{
	int		i;
	long	nbr;

	i = 1;
	while (argv[i])
	{
		nbr = ft_atol(argv[i]);
		if ((i == 1 && nbr <= 0) || (i <= 5 && nbr < 0) || (nbr > INT_MAX))
		{
			dt->ret = -3;
			return (dt);
		}
		i++;
	}
	return (dt);
}
