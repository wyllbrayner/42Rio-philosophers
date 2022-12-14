/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 08:16:40 by bkael             #+#    #+#             */
/*   Updated: 2021/09/29 08:16:59 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_wait(int wait)
{
	int	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < wait)
		usleep(100);
}

void	ft_eat(t_person *person, t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[person->left]);
	ft_print(philo, person->i + 1, "has taken a left fork");
	pthread_mutex_lock(&philo->forks[person->right]);
	ft_print(philo, person->i + 1, "has taken a right fork");
	person->timer = ft_get_time();
	ft_print(philo, person->i + 1, "is eating");
	person->times_eats++;
	ft_wait(philo->eat);
	pthread_mutex_unlock(&philo->forks[person->left]);
	pthread_mutex_unlock(&philo->forks[person->right]);
}

void	*ft_simulate(void *philo)
{
	t_person	*per;
	t_philo		*phi;

	phi = philo;
	per = &phi->persons[phi->i];
	per->timer = ft_get_time();
	while (1)
	{
		ft_eat(per, phi);
		ft_print(phi, per->i + 1, "is sleeping");
		ft_wait(phi->sleep);
		ft_print(phi, per->i + 1, "is thinking");
	}
}

int	ft_pthreads_init(t_philo *philo)
{
	int	i;

	i = 0;
	philo->start = ft_get_time();
	while (i < philo->number_of_philo)
	{
		philo->i = i;
		if (pthread_create(&philo->persons[i].thread, NULL, ft_simulate, philo))
			return (1);
		usleep(100);
		i++;
	}
	return (0);
}
