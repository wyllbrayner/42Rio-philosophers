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

# define FALSE	0     //ainda não usado
# define TRUE	1     //ainda não usado

# define EAT	1
# define SLEEP	2
# define THINK	3

typedef struct      thinker
{
    long            nbr_philo;
    long            philo_n;
    suseconds_t     t_to_die;
    suseconds_t     t_to_eat;
    suseconds_t     t_to_sleep;
    long            must_eat;
    long            just_eat;
    suseconds_t     t_last_eat;
    int             is_live;
    int             actual_action;
    pthread_mutex_t mtx_r_fork;
    pthread_mutex_t mtx_l_fork;
    pthread_mutex_t mtx_print;
}                   t_thinker;

typedef struct      philo
{
    int             ret;
    long            nbr_philo;
    suseconds_t     t_to_die;
    suseconds_t     t_to_eat;
    suseconds_t     t_to_sleep;
    suseconds_t     t_start;
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
//long	ft_get_time(void);
void    ft_setup_destroy(t_setup *t_ph);
void    ft_error(t_setup *t_ph);
void    ft_to_eat(t_thinker *philo);
void    ft_to_sleep(t_thinker *philo);
void    ft_to_think(t_thinker *philo);
t_setup ft_philosophers(int argc, char **argv);
t_setup *ft_check_input(int argc, char **argv, t_setup *t_ph);
t_setup *ft_setup_init(char **argv, t_setup *t_ph);
#endif
