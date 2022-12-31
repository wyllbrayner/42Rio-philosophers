/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_04-monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/12/30 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_philosopher.h"

static int	ft_all_philos_ate(t_philo *phi);
static void	ft_finish_dinner(t_philo *phi);

void	*ft_monitor(void *ptr)
{
	long	i;
	long	current_time;
	long	time_to_die;
	t_philo	*phi;

	phi = (t_philo *)ptr;
	time_to_die = phi->data->time_to_die;
	while (!ft_all_philos_ate(phi))
	{
		i = 0;
		while (i < phi->data->nbr_philos)
		{
			current_time = ft_timenow(phi->data->firststamp);
			if ((current_time - ft_get_last_meal(&phi[i])) > time_to_die)
			{
				ft_finish_dinner(&phi[i]);
				ft_print_action(&phi[i], DIED);
				return (NULL);
			}
			i++;
		}
		ft_msleep(1);
	}
	return (NULL);
}

static int	ft_all_philos_ate(t_philo *phi)
{
	int	i;
	int	had_dinner;

	had_dinner = 0;
	i = -1;
	while (++i < phi->data->nbr_philos)
	{
		if (ft_get_meals(&phi[i]) == phi[i].data->must_eat)
			had_dinner++;
	}
	if (had_dinner == phi->data->nbr_philos)
		return (TRUE);
	return (FALSE);
}

static void	ft_finish_dinner(t_philo *phi)
{
	pthread_mutex_lock(&phi->data->lock_dinner);
	phi->data->dinner_is_over = TRUE;
	pthread_mutex_unlock(&phi->data->lock_dinner);
}
