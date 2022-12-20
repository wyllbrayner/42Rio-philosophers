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

t_setup *ft_philo_init(t_setup *t_ph, int i)
{
    t_ph->philo[i].philo_n = i + 1;
    t_ph->philo[i].nbr_philo = t_ph->nbr_philo;
    t_ph->philo[i].t_to_die = t_ph->t_to_die;
    t_ph->philo[i].t_to_eat = t_ph->t_to_eat;
    t_ph->philo[i].t_to_sleep = t_ph->t_to_sleep;
    t_ph->philo[i].must_eat = t_ph->must_eat;
    t_ph->philo[i].just_eat = 0;
    t_ph->philo[i].t_last_eat = 0;
    t_ph->philo[i].t_start = t_ph->t_start;
    t_ph->philo[i].is_live = 1;
    if (i == (t_ph->nbr_philo - 1))
        t_ph->philo[i].mtx_r_fork = t_ph->fork[0];
    else
        t_ph->philo[i].mtx_r_fork = t_ph->fork[i + 1];
    t_ph->philo[i].mtx_l_fork = t_ph->fork[i];
    t_ph->philo[i].mtx_print = t_ph->mtx_print;
    return (t_ph);
}

t_setup *ft_run_philosophers(t_setup *t_ph)
{
    int i;

    i = 0;
    while (i < t_ph->nbr_philo)
    {
        ft_philo_init(t_ph, i);
        if (pthread_create(&t_ph->thread[i], NULL, &ft_routine, &t_ph->philo[i]) != 0)
        {
            t_ph->ret = -7;
            ft_error(t_ph);
            return (t_ph);
        }
        i++;
    }
    i = 0;
    while (i < t_ph->nbr_philo)
    {
        if (pthread_join(t_ph->thread[i], NULL) != 0)
        {
            t_ph->ret = -8;
            ft_error(t_ph);
            return (t_ph);
        }
        i++;
    }
    return (t_ph);
}

t_setup ft_philosophers(int argc, char **argv)
{
    t_setup t_ph;

    ft_check_input(argc, argv, &t_ph);
    if (t_ph.ret < 0)
        ft_error(&t_ph);
    else
    {
        ft_setup_init(argv, &t_ph);
        if (t_ph.ret < 0)
            ft_error(&t_ph);
	    else
        {
            pthread_mutex_init(&t_ph.mtx_print, NULL);
            ft_run_philosophers(&t_ph);
            pthread_mutex_destroy(&t_ph.mtx_print);
        }
        ft_setup_destroy(&t_ph);
    }
    return (t_ph);
}
