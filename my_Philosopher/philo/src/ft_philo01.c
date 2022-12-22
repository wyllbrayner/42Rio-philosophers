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
    t_ph->philo[i].t_last_eat = t_ph->t_start;
    t_ph->philo[i].t_start = t_ph->t_start;
    t_ph->philo[i].is_live = TRUE;
    t_ph->philo[i].is_running = TRUE;
    if (i == (t_ph->nbr_philo - 1))
        t_ph->philo[i].mtx_r_fork = t_ph->fork[0];
    else
        t_ph->philo[i].mtx_r_fork = t_ph->fork[i + 1];
    t_ph->philo[i].mtx_l_fork = t_ph->fork[i];
    t_ph->philo[i].mtx_print = t_ph->mtx_print;
    return (t_ph);
}

void    ft_stop_philosophers(t_setup *monit)
{
    long    i;

    i = 0;
    while (i < monit->nbr_philo)
    {
        pthread_mutex_lock(&monit->mtx_print);
        monit->philo[i].is_running = FALSE;
        pthread_mutex_unlock(&monit->mtx_print);
        i++;
    }
}

void    *ft_monitor(void *arg)
{
    t_setup *monit;
    long    i;

    monit = (t_setup *)arg;
    usleep(200 * monit->nbr_philo);

    long    full;
    full = 0;
    while (monit->is_running)
    {
        i = 0;
        while (i < monit->nbr_philo)
        {
            if (monit->philo[i].is_live == FALSE)
            {
                usleep(50);
/*
                pthread_mutex_lock(&monit->mtx_print);
                printf("O philosopho: %ld morreu\n", monit->philo[i].philo_n);
                pthread_mutex_unlock(&monit->mtx_print);
*/
                ft_stop_philosophers(monit);
/*
                pthread_mutex_lock(&monit->mtx_print);
                printf("Encerra o monitoramento\n");
                pthread_mutex_unlock(&monit->mtx_print);
*/
                monit->is_running = FALSE;
                break ;
            }
            else if (monit->philo[i].is_running == FALSE)
            {
                full++;
                if (full == (monit->nbr_philo - 1))
                {
                    monit->is_running = FALSE;
                    pthread_mutex_lock(&monit->mtx_print);
                    printf("Everyone has had enough.\n");
                    pthread_mutex_unlock(&monit->mtx_print);
                }
            }
            i++; 
        }
    }
    return (0);
}


t_setup *ft_run_philosophers(t_setup *t_ph)
{
    pthread_t th_monit;
    int i;

    if (pthread_create(&th_monit, NULL, &ft_monitor, t_ph) != 0)
    {
        t_ph->ret = -7; /// depois mudar a sequencia de erros.
        ft_error(t_ph);
        return (t_ph);
    }
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
    if (pthread_join(th_monit, NULL) != 0)
    {
        t_ph->ret = -8;
        ft_error(t_ph);
        return (t_ph);
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
