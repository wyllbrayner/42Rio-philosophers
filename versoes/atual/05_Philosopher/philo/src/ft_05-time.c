/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_05-time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/12/30 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_philosopher.h"

long	ft_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * THOUSAND) + (time.tv_usec / THOUSAND));
}

long	ft_timenow(long firststamp)
{
	return (ft_timestamp() - firststamp);
}

void	ft_msleep(long time_in_ms)
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
