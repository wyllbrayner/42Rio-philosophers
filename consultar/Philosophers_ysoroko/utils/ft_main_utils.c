/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:39:41 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/03 14:39:58 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/// Check the arguments of our program for errors.
/// Returns 1 and displays the corresponding error message if an error is found
/// Returns 0 otherwise.
int	ft_main_args_error(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc > 6 || argc < 5)
		return (ft_puterr("Wrong number of arguments"));
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_strchr(BASE_TEN, argv[i][j]))
				return (ft_puterr("Found non numerical input"));
		}
		if (ft_strlen(argv[i]) > ft_strlen("2147483647")
			|| ft_atol(argv[i]) <= 0 || ft_atol(argv[i]) > INT_MAX)
			return (ft_puterr("Outside integers in range [1 ; 2147483647]"));
	}
	return (0);
}
