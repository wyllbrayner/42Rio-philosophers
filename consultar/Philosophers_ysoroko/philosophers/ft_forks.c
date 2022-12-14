/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 15:36:39 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/02 16:08:29 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/// A special case where there is only one philo
/// In this case only one fork is created, his left one and right one is NULL
/// Returns 0 in case of success, -1 in case of an error
static int	ft_one_philo_fork(t_philo *ph)
{
	pthread_mutex_t	*left_fork;

	left_fork = malloc(sizeof(*left_fork));
	if (!left_fork)
		return (ft_puterr("Failed to malloc a mutex fork"));
	if (pthread_mutex_init(left_fork, NULL))
		return (ft_free_int_ret(left_fork, "Failed to init a mutex fork", -1));
	ph->left_fork = left_fork;
	ph->right_fork = NULL;
	return (0);
}

/// Initializes "displaying" mutex and saves it in philo structure
static int	ft_initialize_displaying_mutex(t_philo *philo)
{
	pthread_mutex_t	*displaying;

	displaying = malloc(sizeof(*displaying));
	if (!displaying)
		return (ft_puterr("Failed to malloc a mutex for display"));
	if (pthread_mutex_init(displaying, NULL))
		return (ft_free_int_ret(displaying, "Failed to init a mutex", -1));
	philo->displaying = displaying;
	return (0);
}

/// This function creates a mutex for every fork and assigns 2 forks to
/// every philosopher, both shared with neighbours.
/// Returns 0 in case of success or -1 in case of an error
int	ft_initialize_forks_mutex(t_philo *ph, int n, t_philo *prev, t_philo *f)
{
	pthread_mutex_t	*left_fork;

	if (!ph)
		return (ft_initialize_displaying_mutex(ph));
	if (n == 1)
		return (ft_one_philo_fork(ph));
	left_fork = malloc(sizeof(*left_fork));
	if (!left_fork)
		return (ft_puterr("Failed to malloc a mutex fork"));
	if (pthread_mutex_init(left_fork, NULL))
		return (ft_free_int_ret(left_fork, "Failed to init a mutex fork", -1));
	if (!prev)
		ph->left_fork = left_fork;
	else if (ph->philo_number == n)
	{
		ph->left_fork = left_fork;
		ph->right_fork = f->left_fork;
		prev->right_fork = left_fork;
	}
	else
	{
		ph->left_fork = left_fork;
		prev->right_fork = left_fork;
	}
	return (0);
}
