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

static int	ft_all_philos_ate(t_philo *philos);
static void	ft_finish_dinner(t_philo *philo);

void	*ft_monitor(void *ptr)
{
	int		i;
	long	current_time;
	long	time_to_die;
	t_philo	*philos;

	philos = (t_philo *)ptr;
	time_to_die = philos->data->time_to_die;
	while (!ft_all_philos_ate(philos))
	{
		i = -1;
		while (++i < philos->data->nbr_philos)
		{
			current_time = ft_timenow(philos->data->firststamp);
			if ((current_time - ft_get_lastsupper(&philos[i])) > time_to_die)
			{
				ft_finish_dinner(&philos[i]);
				ft_print_action(&philos[i], DIED);
				return (NULL);
			}
		}
		ft_msleep(1);
	}
	return (NULL);
}

static int	ft_all_philos_ate(t_philo *philos)
{
	int	i;
	int	had_dinner;

	had_dinner = 0;
	i = -1;
	while (++i < philos->data->nbr_philos)
	{
		if (ft_get_meals(&philos[i]) == philos[i].data->times_must_eat)
			had_dinner++;
	}
	if (had_dinner == philos->data->nbr_philos)
		return (1);
	return (0);
}

static void	ft_finish_dinner(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_dinner);
	philo->data->dinner_is_over = TRUE;
	pthread_mutex_unlock(&philo->data->lock_dinner);
}
