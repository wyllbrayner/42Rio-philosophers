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

static t_setup    *ft_monitor_aux(t_setup *monit);
static void       ft_stop_philosophers(t_setup *monit);

void    *ft_monitor(void *arg)
{
    t_setup *monit;

    monit = (t_setup *)arg;
    usleep(200 * monit->nbr_philo);
    ft_monitor_aux(monit);
    return (0);
}

static t_setup    *ft_monitor_aux(t_setup *monit)
{
    long    full;
    long    i;

    full = -1;
    while (monit->is_running)
    {
        i = -1;
        while (++i < monit->nbr_philo)
        {
            if (monit->philo[i].is_live == FALSE)
            {
                ft_stop_philosophers(monit);
                break ;
            }
            else if (monit->philo[i].is_running == FALSE)
            {
                if (++full == (monit->nbr_philo - 1))
                {
                    monit->is_running = FALSE;
                    break ;
                }
            }
        }
    }
    return (monit);
}

static void    ft_stop_philosophers(t_setup *monit)
{
    long    i;

    i = 0;
    usleep(50);
    while (i < monit->nbr_philo)
    {
        pthread_mutex_lock(&monit->mtx_print);
        monit->philo[i].is_running = FALSE;
        pthread_mutex_unlock(&monit->mtx_print);
        i++;
    }
    monit->is_running = FALSE;
}
