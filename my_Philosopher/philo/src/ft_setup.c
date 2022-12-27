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

static t_setup	*ft_setup_init_aux(t_setup *t_ph);
static void	ft_free(void *arg);

void	ft_error(t_setup *t_ph)
{
	if (t_ph->ret == -1)
		printf("Error: Invalid number of arguments.\n");
	else if ((t_ph->ret == -2) || (t_ph->ret == -3))
		printf("Error: Invalid arguments.\n");
	else if ((t_ph->ret == -4) || (t_ph->ret == -5) || (t_ph->ret == -6))
		printf("Error: Unable to initialize setup.\n");
	else if (t_ph->ret == -7)
		printf("Error: It was not possible to create all threads.\n");
	else if (t_ph->ret == -8)
		printf("Error: It was not possible to group all threads.\n");
}

t_setup	*ft_setup_init(char **argv, t_setup *t_ph)
{
	t_ph->is_running = TRUE;
	t_ph->nbr_philo = ft_atol(argv[1]);
	t_ph->t_to_die = ft_atol(argv[2]);
	t_ph->t_to_eat = ft_atol(argv[3]);
	t_ph->t_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		t_ph->must_eat = ft_atol(argv[5]);
	else
		t_ph->must_eat = 0;
	t_ph->t_start = ft_get_time();
	t_ph->philo = (t_thinker *)malloc(sizeof(t_thinker) * t_ph->nbr_philo);
	if (!t_ph->philo)
	{
		t_ph->ret = -4;
		return (t_ph);
	}
	memset(t_ph->philo, 0, (sizeof(t_thinker) * t_ph->nbr_philo));
	ft_setup_init_aux(t_ph);
	return (t_ph);
}

static t_setup	*ft_setup_init_aux(t_setup *t_ph)
{
	int	i;

	i = 0;
	t_ph->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
			t_ph->nbr_philo);
	if (!t_ph->fork)
	{
		t_ph->ret = -5;
		return (t_ph);
	}
	memset(t_ph->fork, 0, (sizeof(pthread_mutex_t) * t_ph->nbr_philo));
	while (i < t_ph->nbr_philo)
	{
		pthread_mutex_init(&t_ph->fork[i], NULL);
		i++;
	}
	return (t_ph);
}

void	ft_setup_destroy(t_setup *t_ph)
{
	int	i;

	if (t_ph->ret == -5)
		ft_free(t_ph->philo);
	else if ((t_ph->ret == 0) || (t_ph->ret == -7) || (t_ph->ret == -8))
	{
		i = 0;
		while (i < t_ph->nbr_philo)
		{
			pthread_mutex_destroy(&t_ph->fork[i]);
			i++;
		}
		ft_free(t_ph->fork);
		ft_free(t_ph->philo);
	}
}

static void ft_free(void *arg)
{
	free(arg);
	arg = NULL;
}
