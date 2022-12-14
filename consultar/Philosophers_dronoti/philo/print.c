/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:30:45 by bkael             #+#    #+#             */
/*   Updated: 2021/09/16 16:31:02 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_putendl_fd(char *s, int fd)
{
	int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, "\n", 1);
	return (len + 1);
}

void	ft_putnbr(int n)
{
	char	num;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		write(1, "-", 1);
	}
	if (n > 9)
		ft_putnbr(n / 10);
	num = n % 10 + '0';
	write(1, &num, 1);
}

void	ft_print(t_philo *philo, int id, char *str)
{
	int	time;

	time = ft_get_time() - philo->start;
	pthread_mutex_lock(&philo->print);
	ft_putnbr(time);
	write(1, " ", 1);
	ft_putnbr(id);
	write(1, " ", 1);
	ft_putendl_fd(str, 1);
	pthread_mutex_unlock(&philo->print);
}
