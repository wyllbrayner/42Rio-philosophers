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

void	ft_eat(t_thinker *philo)
{
	long	t_eat;

	if (ft_is_alive(philo) && philo->is_running)
	{
		pthread_mutex_lock(&philo->mtx_r_fork);
		pthread_mutex_lock(&philo->mtx_print);
		printf("%ld %ld has taken a fork\n", (ft_get_time() - philo->t_start), \
				philo->philo_n);
		pthread_mutex_lock(&philo->mtx_l_fork);
		printf("%ld %ld has taken a fork\n", (ft_get_time() - philo->t_start), \
				philo->philo_n);
		pthread_mutex_unlock(&philo->mtx_print);
		t_eat = ft_get_time();
		pthread_mutex_lock(&philo->mtx_print);
		philo->just_eat++;
		printf("%ld %ld is eating\n", (t_eat - philo->t_start), philo->philo_n);
		philo->t_last_eat = t_eat;
		usleep(philo->t_to_eat * THOUSAND);
		pthread_mutex_unlock(&philo->mtx_r_fork);
		pthread_mutex_unlock(&philo->mtx_l_fork);
		if (philo->just_eat == (philo->must_eat + 1) && (philo->must_eat != 0))
			philo->is_running = FALSE;
		pthread_mutex_unlock(&philo->mtx_print);
	}
}

void	ft_sleep(t_thinker *philo)
{
	if (ft_is_alive(philo) && philo->is_running)
	{
		pthread_mutex_lock(&philo->mtx_print);
		printf("%ld %ld is sleeping\n", \
			(ft_get_time() - philo->t_start), philo->philo_n);
		pthread_mutex_unlock(&philo->mtx_print);
		ft_smartsleep(philo, philo->t_to_sleep * THOUSAND);
	}
}

void	ft_think(t_thinker *philo)
{
	if (ft_is_alive(philo) && philo->is_running)
	{
		pthread_mutex_lock(&philo->mtx_print);
		printf("%ld %ld is thinking\n", \
			(ft_get_time() - philo->t_start), philo->philo_n);
		pthread_mutex_unlock(&philo->mtx_print);
	}
}

void	*ft_routine(void *arg)
{
	t_thinker	*phi;

	phi = (t_thinker *)arg;
	if ((phi->philo_n % 2) == 0 || ((phi->nbr_philo > 1) && \
			(phi->philo_n == phi->nbr_philo)))
		usleep(phi->t_to_eat);
	if (phi->nbr_philo == 1)
		ft_eat_one(phi);
	else
	{
		while (phi->is_live && ((phi->just_eat < (phi->must_eat + 1)) || \
				phi->must_eat == 0) && phi->is_running)
		{
			ft_eat(phi);
			ft_sleep(phi);
			ft_think(phi);
		}
	}
	pthread_mutex_lock(&phi->mtx_print);
	if (!phi->is_live && phi->is_running)
		printf("%ld %ld died\n", (ft_get_time() - phi->t_start), phi->philo_n);
	else if (phi->just_eat == (phi->must_eat + 1) && (phi->must_eat != 0))
		phi->is_running = FALSE;
	pthread_mutex_unlock(&phi->mtx_print);
	return (0);
}
