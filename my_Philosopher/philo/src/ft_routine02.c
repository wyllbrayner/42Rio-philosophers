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

static long	ft_get_range(long time);

void	ft_msleep(t_thinker *philo, long time)
{
	long	start_time;
	long	sleep;

	start_time = ft_get_time();
	sleep = ft_get_range(time * THOUSAND);
	while (((ft_get_time() - start_time) < time) && ft_is_alive(philo) && philo->is_running)
		usleep(sleep);
}

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
//	return ((time.tv_sec * THOUSAND) + (time.tv_usec / THOUSAND));
	return (((time.tv_sec * 1000000) + time.tv_usec) / THOUSAND);
}

int	ft_is_alive(t_thinker *philo)
{
	if ((ft_get_time() - philo->t_last_eat) > philo->t_to_die)
	{
		philo->is_live = FALSE;
		return (FALSE);
	}
	return (TRUE);
}

void	ft_smartsleep(t_thinker *philo, long time)
{
	long	range;
	long	range_accum;

	pthread_mutex_lock(philo->mtx_print);
	range = ft_get_range((philo->t_to_die - philo->t_to_eat) * THOUSAND);
	range_accum = 0;
	while ((range_accum < time) && ft_is_alive(philo) && philo->is_running)
	{
		if (range_accum < time)
			range = (time - range_accum);
		usleep(range);
		range_accum += range;
	}
	pthread_mutex_unlock(philo->mtx_print);
}

static long	ft_get_range(long time)
{
	if (time >= 10000 && time < 50000)
		return (10000);
	else if (time >= 50000 && time < 100000)
		return (50000);
	else if (time >= 100000 && time < 200000)
		return (100000);
	else if (time >= 200000 && time < 600000)
		return (200000);
	else if (time >= 600000 && time < 1000000)
		return (300000);
	else if (time >= 1000000)
		return (500000);
	else
		return (time);
}
