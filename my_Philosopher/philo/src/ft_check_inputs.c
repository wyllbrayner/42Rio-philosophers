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

static void		ft_valid_input_amount(int argc, t_setup *t_ph);
static t_setup	*ft_valid_input_character(char **argv, t_setup *t_ph);
static int		ft_valid_character(char *str);
static t_setup	*ft_valid_input_number(char **argv, t_setup *t_ph);

t_setup	*ft_check_input(int argc, char **argv, t_setup *t_ph)
{
	t_ph->ret = 0;
    ft_valid_input_amount(argc, t_ph);
    if (t_ph->ret < 0)
        return (t_ph);
    ft_valid_input_character(argv, t_ph);
	if (t_ph->ret < 0)
		return (t_ph);
	ft_valid_input_number(argv, t_ph);
	if (t_ph->ret < 0)
		return (t_ph);
	return (t_ph);
}

static void	ft_valid_input_amount(int argc, t_setup *t_ph)
{
    if (argc < 5 || argc > 6)
        t_ph->ret = -1;
}

static t_setup	*ft_valid_input_character(char **argv, t_setup *t_ph)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (ft_valid_character(argv[i]) < 0)
		{
			t_ph->ret = -2;
			return (t_ph);
		}
		i++;
	}
	return (t_ph);
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
	return (0);
}

static t_setup	*ft_valid_input_number(char **argv, t_setup *t_ph)
{
	int		i;
	long	nbr;

	i = 1;
	while (argv[i])
	{
		nbr = ft_atol(argv[i]);
		if ((i == 1 && nbr <= 0) || (i <= 5 && nbr < 0))
		{
			t_ph->ret = -3;
			return (t_ph);
		}
		i++;
	}
	return (t_ph);
}
