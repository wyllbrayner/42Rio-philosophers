/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_05-time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/12/30 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_philosopher.h"

long	ft_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * THOUSAND) + (time.tv_usec / THOUSAND));
}

long	ft_timenow(long firststamp)
{
	return (ft_timestamp() - firststamp);
}

void	ft_msleep(t_philo *phi, int action)
{
	long	start_time;
	long	time;

	start_time = ft_timestamp();
	time = 0;
	if (action == SLEEPING)
		time = phi->data->time_to_sleep;
	else if (action == EATING)
		time = phi->data->time_to_eat;
	while (((ft_timestamp() - start_time) < time) && (!ft_dinner_is_over(phi)))
		usleep(10);
}

int	ft_dinner_is_over(t_philo *phi)
{
	int	dinner_is_over;

	pthread_mutex_lock(&phi->data->lock_dinner);
	dinner_is_over = FALSE;
	if (phi->data->dinner_is_over)
		dinner_is_over = phi->data->dinner_is_over;
	pthread_mutex_unlock(&phi->data->lock_dinner);
	return (dinner_is_over);
}
