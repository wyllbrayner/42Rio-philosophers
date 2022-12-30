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

int	ft_get_lastsupper(t_philo *philo)
{
	long	lastsupper;

	pthread_mutex_lock(&philo->lock_supper);
	lastsupper = philo->lastsupper;
	pthread_mutex_unlock(&philo->lock_supper);
	return (lastsupper);
}

int	ft_get_meals(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(&philo->lock_meals);
	meals = philo->meals;
	pthread_mutex_unlock(&philo->lock_meals);
	return (meals);
}

void	ft_set_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_meals);
	philo->meals++;
	pthread_mutex_unlock(&philo->lock_meals);
}

void	ft_set_lastsupper(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_supper);
	philo->lastsupper = ft_timenow(philo->data->firststamp);
	pthread_mutex_unlock(&philo->lock_supper);
}

void	ft_print_action(t_philo *philo, int action)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->lock_print);
	current_time = ft_timenow(philo->data->firststamp);
	if (action == TOOK_A_FORK && !ft_dinner_is_over(philo))
		printf("%ld %ld has taken a fork\n", current_time, philo->id);
	else if (action == EATING && !ft_dinner_is_over(philo))
		printf("%ld %ld is eating\n", current_time, philo->id);
	else if (action == SLEEPING && !ft_dinner_is_over(philo))
		printf("%ld %ld is sleeping\n", current_time, philo->id);
	else if (action == THINKING && !ft_dinner_is_over(philo))
		printf("%ld %ld is thinking\n", current_time, philo->id);
	else if (action == DIED)
		printf("%ld %ld died\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->data->lock_print);
}
