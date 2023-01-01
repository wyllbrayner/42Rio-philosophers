/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_03-00_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/12/30 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_philosopher.h"

static void	*ft_eat_one(t_philo *phi);
static void	ft_to_eat(t_philo *phi);
static void	ft_to_sleep(t_philo *phi);
static void	ft_to_think(t_philo *phi);

void	*ft_actions(void *ptr)
{
	t_philo	*phi;

	phi = (t_philo *)ptr;
	if (phi->data->nbr_philos == 1)
		return (ft_eat_one(phi));
	if (phi->id % 2)
		usleep(THOUSAND);
//		ft_msleep(5); //
	while (!ft_dinner_is_over(phi))
	{
		ft_to_eat(phi);
		if (ft_get_meals(phi) == (phi->data->must_eat + 1))
			return (NULL);
		ft_to_sleep(phi);
		ft_to_think(phi);
	}
	return (NULL);
}

static void	*ft_eat_one(t_philo *phi)
{
	pthread_mutex_lock(phi->fork_right);
	ft_print_action(phi, TOOK_A_FORK);
	pthread_mutex_unlock(phi->fork_right);
	return (NULL);
}

static void	ft_to_eat(t_philo *phi)
{
	pthread_mutex_lock(phi->fork_right);
	pthread_mutex_lock(phi->fork_left);
	if (ft_dinner_is_over(phi))
	{
		pthread_mutex_unlock(phi->fork_right);
		pthread_mutex_unlock(phi->fork_left);
		return ;
	}
	ft_print_action(phi, TOOK_A_FORK);
	ft_print_action(phi, TOOK_A_FORK);
	ft_print_action(phi, EATING);
	ft_set_last_meal(phi);
//	ft_msleep(phi->data->time_to_eat); //
	ft_msleep(phi, EATING);
	pthread_mutex_unlock(phi->fork_right);
	pthread_mutex_unlock(phi->fork_left);
	ft_set_meals(phi);
}

static void	ft_to_sleep(t_philo *phi)
{
	ft_print_action(phi, SLEEPING);
//	ft_msleep(phi->data->time_to_sleep); //
	ft_msleep(phi, SLEEPING);
}

static void	ft_to_think(t_philo *phi)
{
	ft_print_action(phi, THINKING);
}
