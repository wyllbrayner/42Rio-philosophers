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

static void	*ft_eat_one(t_philo *philo);
static void	ft_to_eat(t_philo *philo);
static void	ft_to_sleep(t_philo *philo);
static void	ft_to_think(t_philo *philo);

void	*ft_actions(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->data->nbr_philos == 1)
		return (ft_eat_one(philo));
	if (philo->id % 2)
		ft_msleep(5);
	while (!ft_dinner_is_over(philo))
	{
		ft_to_eat(philo);
		if (ft_get_meals(philo) == (philo->data->must_eat + 1))
			return (NULL);
		ft_to_sleep(philo);
		ft_to_think(philo);
	}
	return (NULL);
}

static void	*ft_eat_one(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	ft_print_action(philo, TOOK_A_FORK);
	pthread_mutex_unlock(philo->fork_right);
	return (NULL);
}

static void	ft_to_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(philo->fork_left);
	if (ft_dinner_is_over(philo))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return ;
	}
	ft_print_action(philo, TOOK_A_FORK);
	ft_print_action(philo, TOOK_A_FORK);
	ft_print_action(philo, EATING);
	ft_set_last_meal(philo);
	ft_msleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	ft_set_meals(philo);
}

static void	ft_to_sleep(t_philo *philo)
{
	ft_print_action(philo, SLEEPING);
	ft_msleep(philo->data->time_to_sleep);
}

static void	ft_to_think(t_philo *philo)
{
	ft_print_action(philo, THINKING);
}


