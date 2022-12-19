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

/*
void ft_to_eat(t_thinker *philo)
{
    long t_eat;

    pthread_mutex_lock(&philo->mtx_r_fork);
    pthread_mutex_lock(&philo->mtx_l_fork);
    pthread_mutex_lock(&philo->mtx_print);
    printf("%ld %ld has taken a fork\n", (ft_get_time() - philo->t_last_eat), philo->philo_n);
    printf("%ld %ld has taken a fork\n", (ft_get_time() - philo->t_last_eat), philo->philo_n);
    t_eat = ft_get_time();
    printf("%ld %ld is eating\n", (t_eat - philo->t_last_eat), philo->philo_n);
    philo->t_last_eat = t_eat;
    pthread_mutex_unlock(&philo->mtx_print);
    pthread_mutex_unlock(&philo->mtx_r_fork);
    pthread_mutex_unlock(&philo->mtx_l_fork);
}
*/

void ft_to_eat(t_thinker *philo)
{
    long    t_eat;

    pthread_mutex_lock(&philo->mtx_r_fork);
    pthread_mutex_lock(&philo->mtx_print);
//    printf("%ld %ld has taken a fork\n", (ft_get_time() - philo->t_last_eat), philo->philo_n);
    printf("t_last_eat: %d\n", philo->t_last_eat);
    t_eat = ft_get_time();
    printf("t_eat     : %ld\n", t_eat);
    printf("diferença : %ld\n", t_eat - philo->t_last_eat);
    printf("%ld %ld has taken a fork\n", (t_eat - philo->t_last_eat), philo->philo_n);
    if (philo->nbr_philo != 1)
    {
        pthread_mutex_lock(&philo->mtx_l_fork);
        printf("%ld %ld has taken a fork\n", (ft_get_time() - philo->t_last_eat), philo->philo_n);
        t_eat = ft_get_time();
        printf("%ld %ld is eating\n", (t_eat - philo->t_last_eat), philo->philo_n);
        philo->t_last_eat = t_eat;
        usleep(philo->t_to_eat * 1000);
        philo->actual_action = EAT;
        pthread_mutex_unlock(&philo->mtx_r_fork);
        pthread_mutex_unlock(&philo->mtx_l_fork);
        pthread_mutex_unlock(&philo->mtx_print);
    }
}
/*
*/

void ft_to_sleep(t_thinker *philo)
{
    pthread_mutex_lock(&philo->mtx_print);
    printf("%ld %ld is sleeping\n", (ft_get_time() - philo->t_last_eat), philo->philo_n);
    usleep(philo->t_to_sleep * 1000);
    philo->actual_action = SLEEP;
    pthread_mutex_unlock(&philo->mtx_print);
}

void ft_to_think(t_thinker *philo)
{
    pthread_mutex_lock(&philo->mtx_print);
    printf("%ld %ld is thinking\n", (ft_get_time() - philo->t_last_eat), philo->philo_n);
    philo->actual_action = THINK;
    pthread_mutex_unlock(&philo->mtx_print);
}

void *ft_routine(void *arg)
{
    int i;
    t_thinker *philo;

    i = 0;
    philo = (t_thinker *)arg;
    while (philo->is_live)
    {
        if ((philo->philo_n % 2) && i == 0)
            usleep((philo->t_to_eat * 1000) * 0.2);
        ft_to_eat(philo);
        ft_to_sleep(philo);
        ft_to_think(philo);
        if (i == 10)
            philo->is_live = 0;
        i++;
    }
    pthread_mutex_lock(&philo->mtx_print);
    printf("O philosopho %ld terminou\n", philo->philo_n);
    pthread_mutex_unlock(&philo->mtx_print);
    return (0);
}

t_setup *ft_philo_init(t_setup *t_ph, int i)
{
    t_ph->philo[i].nbr_philo = t_ph->nbr_philo;
    t_ph->philo[i].philo_n = i + 1;
    t_ph->philo[i].t_to_die = t_ph->t_to_die;
    t_ph->philo[i].t_to_eat = t_ph->t_to_eat;
    t_ph->philo[i].t_to_sleep = t_ph->t_to_sleep;
    t_ph->philo[i].must_eat = t_ph->must_eat;
    t_ph->philo[i].just_eat = 0;
    t_ph->philo[i].t_last_eat = t_ph->t_start;
    t_ph->philo[i].is_live = 1;
    t_ph->philo[i].actual_action = 0;

//    printf("Inicio do philo: %ld | t_to_die: %ld | t_to_eat: %ld | t_to_sleep: %ld | must_eat: %ld | just_eat: %ld | t_last_eat: %ld | is_live: %d | actual_action: %d ", t_ph->philo[i].philo_n, t_ph->philo[i].t_to_die, t_ph->philo[i].t_to_eat, t_ph->philo[i].t_to_sleep, t_ph->philo[i].must_eat, t_ph->philo[i].just_eat, t_ph->philo[i].t_last_eat, t_ph->philo[i].is_live, t_ph->philo[i].actual_action);
    printf("Inicio do philo: %ld | t_to_die: %d | t_to_eat: %d | t_to_sleep: %d | must_eat: %ld | just_eat: %ld | t_last_eat: %d | is_live: %d | actual_action: %d ", t_ph->philo[i].philo_n, t_ph->philo[i].t_to_die, t_ph->philo[i].t_to_eat, t_ph->philo[i].t_to_sleep, t_ph->philo[i].must_eat, t_ph->philo[i].just_eat, t_ph->philo[i].t_last_eat, t_ph->philo[i].is_live, t_ph->philo[i].actual_action);
    if (i == (t_ph->nbr_philo - 1))
    {
        t_ph->philo[i].mtx_r_fork = t_ph->fork[0];
        printf("| r_fork : 0");
    }
    else
    {
        t_ph->philo[i].mtx_r_fork = t_ph->fork[i + 1];
        printf("| r_fork : %d", (i + 1));
    }
    t_ph->philo[i].mtx_l_fork = t_ph->fork[i];
    t_ph->philo[i].mtx_print = t_ph->mtx_print;
    printf(" | l_fork : %d\n", i);
    return (t_ph);
}

t_setup *ft_run_philosophers(t_setup *t_ph)
{
    int         i;

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
/*
*/
        i++;
    }
/*
*/
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
