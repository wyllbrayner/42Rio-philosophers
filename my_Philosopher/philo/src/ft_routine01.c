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

static void	ft_eat_one(t_thinker *philo);
static void	ft_eat(t_thinker *philo);
static void	ft_sleep(t_thinker *philo);
static void	ft_think(t_thinker *philo);

void	*ft_routine(void *arg)
{
	t_thinker	*p;

	p = (t_thinker *)arg;
	if ((p->philo_n % 2) == 0 || ((p->nbr_philo > 1) && (p->philo_n == p->nbr_philo)))
		usleep(p->t_to_eat * 10);
	if (p->nbr_philo == 1)
		ft_eat_one(p);
	else
	{
		while (p->is_live && ((p->just_eat < (p->must_eat + 1)) || \
				p->must_eat == 0) && p->is_running)
		{
			ft_eat(p);
			ft_sleep(p);
			ft_think(p);
		}
	}
	pthread_mutex_lock(p->mtx_print);
	if (!p->is_live && p->is_running)
		printf("%ld %ld died\n", (ft_get_time() - p->t_start), p->philo_n);
	else if (p->just_eat == (p->must_eat + 1) && (p->must_eat != 0))
		p->is_running = FALSE;
	pthread_mutex_unlock(p->mtx_print);
	return (0);
}

static void	ft_eat_one(t_thinker *philo)
{
	if (ft_is_alive(philo) && philo->is_running)
	{
		pthread_mutex_lock(philo->mtx_r_fork);
		pthread_mutex_lock(philo->mtx_print);
		printf("%ld %ld has taken a fork\n", (ft_get_time() - philo->t_start), \
			philo->philo_n);
		pthread_mutex_unlock(philo->mtx_print);
		while (ft_is_alive(philo))
//			ft_msleep(philo, philo->t_to_sleep);
			ft_smartsleep(philo, philo->t_to_sleep);
		pthread_mutex_unlock(philo->mtx_r_fork);
	}
}

static void	ft_eat(t_thinker *philo)
{
	long	t_eat;

	if (ft_is_alive(philo) && philo->is_running)
	{
		pthread_mutex_lock(philo->mtx_r_fork);
//		pthread_mutex_lock(philo->mtx_print);
		printf("%ld %ld locked the r_fork %p\n", (ft_get_time() - philo->t_start), \
				philo->philo_n, philo->mtx_r_fork);
/*
		printf("%ld %ld has taken a fork\n", (ft_get_time() - philo->t_start), \
				philo->philo_n);
*/
		pthread_mutex_lock(philo->mtx_l_fork);
		printf("%ld %ld locked the l_fork %p\n", (ft_get_time() - philo->t_start), \
				philo->philo_n, philo->mtx_l_fork);
/*
		printf("%ld %ld has taken a fork\n", (ft_get_time() - philo->t_start), \
				philo->philo_n);
*/
//		pthread_mutex_unlock(philo->mtx_print);
		pthread_mutex_lock(philo->mtx_print);
		t_eat = ft_get_time();
		philo->just_eat++;
		printf("%ld %ld is eating\n", (t_eat - philo->t_start), philo->philo_n);
		philo->t_last_eat = t_eat;
		usleep(philo->t_to_eat * THOUSAND);
//		ft_msleep(philo, philo->t_to_eat);
		pthread_mutex_unlock(philo->mtx_r_fork);
		printf("%ld %ld unlocked the r_fork %p\n", (ft_get_time() - philo->t_start), \
				philo->philo_n, philo->mtx_r_fork);
		pthread_mutex_unlock(philo->mtx_l_fork);
		printf("%ld %ld unlocked the l_fork %p\n", (ft_get_time() - philo->t_start), \
				philo->philo_n, philo->mtx_l_fork);
		if (philo->just_eat == (philo->must_eat + 1) && (philo->must_eat != 0))
			philo->is_running = FALSE;
		pthread_mutex_unlock(philo->mtx_print);
	}
}

static void	ft_sleep(t_thinker *philo)
{
	if (ft_is_alive(philo) && philo->is_running)
	{
		pthread_mutex_lock(philo->mtx_print);
		printf("%ld %ld is sleeping\n", \
			(ft_get_time() - philo->t_start), philo->philo_n);
		pthread_mutex_unlock(philo->mtx_print);
		ft_msleep(philo, philo->t_to_sleep);
//		ft_smartsleep(philo, philo->t_to_sleep * THOUSAND);
	}
}

static void	ft_think(t_thinker *philo)
{
	if (ft_is_alive(philo) && philo->is_running)
	{
		pthread_mutex_lock(philo->mtx_print);
		printf("%ld %ld is thinking\n", \
			(ft_get_time() - philo->t_start), philo->philo_n);
		pthread_mutex_unlock(philo->mtx_print);
	}
}