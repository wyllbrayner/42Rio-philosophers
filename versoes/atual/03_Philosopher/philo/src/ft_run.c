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


static t_philo *ft_start_philosophers_aux(long n, t_philo *philos, pthread_t monitor_thread);

t_philo *ft_start_philosophers(long n, t_philo *philos)
{
	long			i;
	pthread_t	monitor_thread;

	i = 0;
	philos->data->firststamp = ft_timestamp();
	while (i < n)
	{
		if (pthread_create(&philos[i].thread, NULL, &ft_actions, &philos[i]) != 0)
		{
			(philos->data)->ret = -6;
			ft_error(philos->data);
			return (philos);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, &ft_monitor, philos) != 0)
	{
		(philos->data)->ret = -6;
		ft_error(philos->data);
		return (philos);
	}
	ft_start_philosophers_aux(n, philos, monitor_thread);
	return (philos);
}

static t_philo *ft_start_philosophers_aux(long n, t_philo *philos, pthread_t monitor_thread)
{
	long			i;

	i = 0;
	while (i < n)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
		{
			(philos->data)->ret = -7;
			ft_error(philos->data);
			return (philos);
		}
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		(philos->data)->ret = -7;
		ft_error(philos->data);
		return (philos);
	}
	return (philos);
}
