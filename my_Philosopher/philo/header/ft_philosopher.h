/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/07/09 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOSOPHER_H
# define FT_PHILOSOPHER_H

# include <stdio.h>   // printf
# include <stdlib.h>  // malloc e free
# include <unistd.h>  // sleep
# include <string.h>  // memset
# include <pthread.h> // thread
# include <sys/time.h>// gettimeofday

# define INT_MAX 2147483647
# define FALSE	0
# define TRUE	1

typedef struct      thinker
{
    long            philo_n;
    long            nbr_philo;
    long            t_to_die;
    long            t_to_eat;
    long            t_to_sleep;
    long            must_eat;
    long            just_eat;
    long            t_last_eat;
    long            t_start;
    int             is_live;
    pthread_mutex_t mtx_r_fork;
    pthread_mutex_t mtx_l_fork;
    pthread_mutex_t mtx_print;
}                   t_thinker;

typedef struct      philo
{
    int             ret;
    long            nbr_philo;
    long            t_to_die;
    long            t_to_eat;
    long            t_to_sleep;
    long            t_start;
    long            must_eat;
    int             is_running;
    t_thinker       *philo;
    pthread_mutex_t *fork;
    pthread_t       *thread;
    pthread_mutex_t mtx_print;
}                   t_setup;

int     ft_isspace(int c);
int     ft_isdigit(int c);
long    ft_atol(char *str);
long    ft_get_time(void);
void    *ft_routine(void *arg);
void    ft_setup_destroy(t_setup *t_ph);
void    ft_error(t_setup *t_ph);
t_setup ft_philosophers(int argc, char **argv);
t_setup *ft_check_input(int argc, char **argv, t_setup *t_ph);
t_setup *ft_setup_init(char **argv, t_setup *t_ph);
#endif
