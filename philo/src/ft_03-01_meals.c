/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_03-01_meals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/12/30 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_philosopher.h"

long	ft_get_last_meal(t_philo *phi)
{
	long	t_last_meal;

	pthread_mutex_lock(&phi->lock_t_last_meal);
	t_last_meal = phi->t_last_meal;
	pthread_mutex_unlock(&phi->lock_t_last_meal);
	return (t_last_meal);
}

long	ft_get_meals(t_philo *phi)
{
	int	meals;

	pthread_mutex_lock(&phi->lock_meals);
	meals = phi->meals;
	pthread_mutex_unlock(&phi->lock_meals);
	return (meals);
}

void	ft_set_meals(t_philo *phi)
{
	pthread_mutex_lock(&phi->lock_meals);
	phi->meals++;
	pthread_mutex_unlock(&phi->lock_meals);
}

void	ft_set_last_meal(t_philo *phi)
{
	pthread_mutex_lock(&phi->lock_t_last_meal);
	phi->t_last_meal = ft_timenow(phi->data->firststamp);
	pthread_mutex_unlock(&phi->lock_t_last_meal);
}

void	ft_print_action(t_philo *phi, int action)
{
	long	current_time;

	pthread_mutex_lock(&phi->data->lock_print);
	current_time = ft_timenow(phi->data->firststamp);
	if (!ft_dinner_is_over(phi))
	{
		if (action == TOOK_A_FORK)
			printf("%ld %ld has taken a fork\n", current_time, phi->id);
		else if (action == EATING)
			printf("%ld %ld is eating\n", current_time, phi->id);
		else if (action == SLEEPING)
			printf("%ld %ld is sleeping\n", current_time, phi->id);
		else if (action == THINKING)
			printf("%ld %ld is thinking\n", current_time, phi->id);
	}
	else if (action == DIED)
		printf("%ld %ld died\n", current_time, phi->id);
	pthread_mutex_unlock(&phi->data->lock_print);
}
