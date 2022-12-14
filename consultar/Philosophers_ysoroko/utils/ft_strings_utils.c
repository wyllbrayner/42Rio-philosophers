/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:43:38 by ysoroko           #+#    #+#             */
/*   Updated: 2021/08/25 11:53:28 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/// Calculates the length of the string (without ending '\0') and returns it
int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

/// Checks if character c (int argument) is present is str string argument.
/// Returns the adress of the first occurence of c in str if it's found.
/// Returns a NULL pointer if c isn't present in str.
char	*ft_strchr(char *str, int c)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			return (&str[i]);
		}
		i++;
	}
	if (str[i] == c)
	{
		return (&str[i]);
	}
	return (0);
}

/// Returns 1 if the character c argument is a digit, 0 otherwise.
int	ft_isnum(char c)
{
	if (ft_strchr(BASE_TEN, c))
		return (1);
	return (0);
}

/// Converts the string str to a long number and returns this number
/// Returns 0 if str is composed of non-digit characters.
long	ft_atol(char *str)
{
	int		i;
	long	ret;
	int		sign;

	i = 0;
	ret = 0;
	sign = 1;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && ft_isnum(str[i]))
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return (ret * sign);
}

/// Displays "Error" followed by its argument on STDERR (in red color)
/// Returns a NULL pointer
void	*ft_puterr_ptr(char *str)
{
	if (!str)
		return (NULL);
	ft_putstr_fd(BOLDRED, STDERR);
	ft_putendl_fd("Error:\t", STDERR);
	ft_putendl_fd(str, STDERR);
	ft_putstr_fd(COLOR_RESET, STDERR);
	return (NULL);
}
