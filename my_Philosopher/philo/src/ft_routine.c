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

int ft_is_alive(t_thinker *philo)
{
    if ((ft_get_time() - philo->t_last_eat) > philo->t_to_die)
    {
        philo->is_live = FALSE;
        return (FALSE);
    }
    return (TRUE);
}

long ft_get_range(long time)
{
    if (time >= 10000 && time < 50000)
        return (10000);
    else if (time >= 50000 && time < 100000)
        return (50000);
    else if (time >= 100000 && time < 200000)
        return (100000);
    else if (time > 200000)
        return (200000);
    else
        return (time);
}

void	ft_smartsleep(t_thinker *philo, long time)
{
    long    range;
    long    range_accum;

    range = ft_get_range((philo->t_to_die - philo->t_to_eat) * THOUSAND);
    range_accum = 0;
    while ((range_accum < time) && ft_is_alive(philo))
    {
        usleep(range);
        range_accum += range;
        if (range_accum < time)
            range = (time - range_accum);
    }
}

void ft_eat_one(t_thinker *philo)
{
    pthread_mutex_lock(&philo->mtx_r_fork);
    pthread_mutex_lock(&philo->mtx_print);
    printf("%ld %ld has taken a fork\n", (ft_get_time() - philo->t_start), philo->philo_n);
    pthread_mutex_unlock(&philo->mtx_print);
    while(ft_is_alive(philo))
        ft_smartsleep(philo, philo->t_to_sleep);
    pthread_mutex_unlock(&philo->mtx_r_fork);
}

void ft_eat(t_thinker *philo)
{
    long    t_eat;

    pthread_mutex_lock(&philo->mtx_r_fork);
    pthread_mutex_lock(&philo->mtx_print);
    printf("%ld %ld has taken a fork\n", (ft_get_time() - philo->t_start), philo->philo_n);
    pthread_mutex_lock(&philo->mtx_l_fork);
    printf("%ld %ld has taken a fork\n", (ft_get_time() - philo->t_start), philo->philo_n);
    pthread_mutex_unlock(&philo->mtx_print);
    t_eat = ft_get_time();
    pthread_mutex_lock(&philo->mtx_print);
    printf("%ld %ld is eating\n", (t_eat - philo->t_start), philo->philo_n);
    philo->t_last_eat = t_eat;
    usleep(philo->t_to_eat * THOUSAND);
    pthread_mutex_unlock(&philo->mtx_r_fork);
    pthread_mutex_unlock(&philo->mtx_l_fork);
    pthread_mutex_unlock(&philo->mtx_print);
}

void ft_sleep(t_thinker *philo)
{
    if (ft_is_alive(philo))
    {
        pthread_mutex_lock(&philo->mtx_print);
        printf("%ld %ld is sleeping\n", (ft_get_time() - philo->t_start), philo->philo_n);
        pthread_mutex_unlock(&philo->mtx_print);
//        usleep(philo->t_to_sleep * THOUSAND);
        ft_smartsleep(philo, philo->t_to_sleep * THOUSAND);
    }
}

void ft_think(t_thinker *philo)
{
    if (ft_is_alive(philo))
    {
        pthread_mutex_lock(&philo->mtx_print);
        printf("%ld %ld is thinking\n", (ft_get_time() - philo->t_start), philo->philo_n);
        pthread_mutex_unlock(&philo->mtx_print);
    }
}

void *ft_routine(void *arg)
{
    t_thinker *philo;

    philo = (t_thinker *)arg;
//    if ((philo->philo_n % 2) == 0 || ((philo->nbr_philo > 1) && (philo->philo_n == philo->nbr_philo)))
//        usleep(philo->t_to_eat);
    if ((philo->philo_n % 2) == 0)
        usleep(philo->t_to_eat);
    if (philo->nbr_philo == 1)
        ft_eat_one(philo);
    else
    {
        while (philo->is_live && ((philo->just_eat < philo->must_eat) || philo->must_eat == 0))
        {
            ft_eat(philo);
            philo->just_eat++;
            ft_sleep(philo);
            ft_think(philo);
        }
    }
    pthread_mutex_lock(&philo->mtx_print);
    if (!philo->is_live)
        printf("%ld %ld died\n", (ft_get_time() - philo->t_start), philo->philo_n);
    else
        printf("%ld O filosofo %ld terminou pois comeu %ld de %ld\n",(ft_get_time() - philo->t_start) ,philo->philo_n, philo->just_eat, philo->must_eat);
    pthread_mutex_unlock(&philo->mtx_print);
    return (0);
}
