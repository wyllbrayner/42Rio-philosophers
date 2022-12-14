/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvaz-fe <igvaz-fe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:42:22 by igvaz-fe          #+#    #+#             */
/*   Updated: 2022/03/24 18:54:00 by igvaz-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	long	current_time;

	current_time = get_time() - philo->setup_philo->start_time;
	pthread_mutex_lock(&philo->setup_philo->print_locker);
	if (!philo->setup_philo->is_died)
		printf("%5ld %3d %s\n", current_time, philo->philo_id, action);
	pthread_mutex_unlock(&philo->setup_philo->print_locker);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check_meals(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->setup_philo->times_to_eat > 0)
	{
		while (i < philo->setup_philo->n_philos)
		{
			if (philo[i].n_meals >= philo->setup_philo->times_to_eat)
				philo->setup_philo->meals++;
			i++;
		}
		if (philo->setup_philo->meals >= philo->setup_philo->n_philos)
		{
			philo->setup_philo->is_died = 1;
			return (1);
		}
	}
	return (0);
}
