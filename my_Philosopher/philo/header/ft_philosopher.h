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

# include <pthread.h> // thread

# define FALSE	0
# define TRUE	1

typedef struct      thinker
{
    pthread_t   th;
}                   t_thinker;


typedef struct      philo
{
    int             ret;
    long            nbr_philo;
    long            nbr_fork;
    suseconds_t     t_to_die;
    suseconds_t     t_to_eat;
    suseconds_t     t_to_sleep;
    long            t_must_eat;
}                   t_philo;

long    ft_atol(char *str);
int     ft_isspace(int c);
int     ft_isdigit(int c);
int     ft_valid_character(char *str);
t_philo ft_philosophers(int argc, char **argv);
t_philo *ft_valid_input_number(char **argv, t_philo *t_ph);
t_philo *ft_valid_input_character(char **argv, t_philo *t_ph);
t_philo *ft_check_input(int argc, char **argv, t_philo *t_ph);
void    ft_valid_input_amount(int argc, t_philo *t_ph);
void    ft_init_struct(char **argv, t_philo *t_ph);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
long	get_time(void);

#endif
