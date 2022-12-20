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

static t_setup  *ft_setup_init_aux(t_setup *t_ph);
static void     ft_setup_destroy_aux(t_setup *t_ph);

void    ft_error(t_setup *t_ph)
{
	if (t_ph->ret == -1)
		printf("Error: Invalid number of arguments.\n");
	else if ((t_ph->ret == -2) || (t_ph->ret == -3))
        printf("Error: Invalid arguments.\n");
	else if ((t_ph->ret == -4) || (t_ph->ret == -5) || (t_ph->ret == -6))
        printf("Error: Unable to initialize setup.\n");
	else if (t_ph->ret == -7)
        printf("Error: It was not possible to create all philosophers.\n");
	else if (t_ph->ret == -8)
        printf("Error: It was not possible to group all philosophers.\n");
}

t_setup *ft_setup_init(char **argv, t_setup *t_ph)
{
    t_ph->nbr_philo = ft_atol(argv[1]);
    t_ph->t_to_die = ft_atol(argv[2]);
    t_ph->t_to_eat = ft_atol(argv[3]);
    t_ph->t_to_sleep = ft_atol(argv[4]);
    t_ph->t_start = ft_get_time();
    if (argv[5])
        t_ph->must_eat = ft_atol(argv[5]);
    else
        t_ph->must_eat = 0;
    t_ph->is_running = 1;
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

static t_setup  *ft_setup_init_aux(t_setup *t_ph)
{
    int i;

    i = 0;
    t_ph->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * t_ph->nbr_philo);
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
    t_ph->thread = (pthread_t *)malloc(sizeof(pthread_t) * t_ph->nbr_philo);
    if (!t_ph->thread)
    {
        t_ph->ret = -6;
        return (t_ph);
    }
    memset(t_ph->thread, 0, sizeof(pthread_t) * t_ph->nbr_philo);
    return (t_ph);
}

void    ft_setup_destroy(t_setup *t_ph)
{
    if (t_ph->ret == -5)
    {
        free(t_ph->philo);
        t_ph->philo = NULL;
    }
    else if (t_ph->ret == -6)
    {
        free(t_ph->fork);
        t_ph->fork = NULL;
        free(t_ph->philo);
        t_ph->philo = NULL;
    }
    else if ((t_ph->ret == 0) || (t_ph->ret == -7) || (t_ph->ret == -8))
    {
        ft_setup_destroy_aux(t_ph);
        free(t_ph->thread);
        t_ph->thread = NULL;
        free(t_ph->fork);
        t_ph->fork = NULL;
        free(t_ph->philo);
        t_ph->philo = NULL;
    }
}

static void ft_setup_destroy_aux(t_setup *t_ph)
{
    int i;

    i = 0;
    while (i < t_ph->nbr_philo)
    {
        pthread_mutex_destroy(&t_ph->fork[i]);
        i++;
    }
}
