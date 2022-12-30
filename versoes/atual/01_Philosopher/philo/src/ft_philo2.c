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

int	get_lastsupper(t_philo *philo) // ok
{
	long	lastsupper;

	pthread_mutex_lock(&philo->lock_supper);
	lastsupper = philo->lastsupper;
	pthread_mutex_unlock(&philo->lock_supper);
	return (lastsupper);
}

int	get_meals(t_philo *philo) // ok
{
	int	meals;

	pthread_mutex_lock(&philo->lock_meals);
	meals = philo->meals;
	pthread_mutex_unlock(&philo->lock_meals);
	return (meals);
}

void	set_meals(t_philo *philo) // ok
{
	pthread_mutex_lock(&philo->lock_meals);
	philo->meals++;
	pthread_mutex_unlock(&philo->lock_meals);
}

void	set_lastsupper(t_philo *philo) //ok
{
	pthread_mutex_lock(&philo->lock_supper);
	philo->lastsupper = timenow(philo->data->firststamp);
	pthread_mutex_unlock(&philo->lock_supper);
}

long	timestamp(void) //ok
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	timenow(long firststamp) // ok
{
	return (timestamp() - firststamp);
}

void	msleep(int time_in_ms)  //ok verificar se não devo proteger essa função com mutex
{
	long	start_time;

	start_time = timestamp();
	while ((timestamp() - start_time) < (long)time_in_ms)
		usleep(10);
}