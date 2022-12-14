/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvaz-fe <igvaz-fe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:29:19 by igvaz-fe          #+#    #+#             */
/*   Updated: 2022/03/24 18:57:39 by igvaz-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*only_one(t_philo *philo)
{
	pthread_mutex_lock(&philo->setup_philo->forks[philo->left_fork]);
	print_action(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->setup_philo->forks[philo->left_fork]);
	print_action(philo, "died");
	philo->setup_philo->is_died = 1;
	return (NULL);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->setup_philo->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->setup_philo->forks[philo->right_fork]);
	print_action(philo, "has taken a fork");
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	philo->last_meal = get_time();
	usleep(philo->setup_philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->setup_philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->setup_philo->forks[philo->right_fork]);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->setup_philo->n_philos == 1)
		return (only_one(philo));
	if (philo->philo_id % 2 == 0)
		usleep(1600);
	while (philo->setup_philo->is_died != 1)
	{
		eating(philo);
		print_action(philo, "is sleeping");
		usleep(philo->setup_philo->time_to_sleep * 1000);
		print_action(philo, "is thinking");
		philo->n_meals++;
	}
	return (NULL);
}

void	*monitoring(void *ptr)
{
	int		i;
	t_philo	*p;

	p = (t_philo *)ptr;
	while (!check_meals(p))
	{
		i = 0;
		while (i < p->setup_philo->n_philos)
		{
			if (get_time() - p[i].last_meal > p->setup_philo->time_to_die)
			{
				print_action(&p[i], "died");
				p->setup_philo->is_died = 1;
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	start_dinner(t_philo *philo)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	philo->setup_philo->start_time = get_time();
	while (i < philo->setup_philo->n_philos)
	{
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, &monitoring, philo);
	i = 0;
	while (i < philo->setup_philo->n_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}
