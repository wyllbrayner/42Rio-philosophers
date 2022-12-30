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

long	ft_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	ft_timenow(long firststamp)
{
	return (ft_timestamp() - firststamp);
}

void	ft_msleep(long time_in_ms)  //ok verificar se não devo proteger essa função com mutex
{
	long	start_time;

	start_time = ft_timestamp();
	while ((ft_timestamp() - start_time) < time_in_ms)
		usleep(10);
}

int	ft_dinner_is_over(t_philo *philo)
{
	int	dinner_is_over;

	pthread_mutex_lock(&philo->data->lock_dinner);
	dinner_is_over = FALSE;
	if (philo->data->dinner_is_over)
		dinner_is_over = philo->data->dinner_is_over;
	pthread_mutex_unlock(&philo->data->lock_dinner);
	return (dinner_is_over);
}