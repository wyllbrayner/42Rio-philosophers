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

# include <errno.h>   //pode usar?
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>  //memset
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define THOUSAND 1000
# define FALSE	0
# define TRUE	1

# define TOOK_A_FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5

typedef pthread_mutex_t	t_mutex;

typedef struct s_data
{
	int				ret;
	int				alone;
	long				number_of_philos;//s
	long				dinner_is_over;//s
	long				time_to_die;   //s
	long				time_to_eat;   //s
	long				time_to_sleep; //s
	long				times_must_eat;//s
	long			firststamp;    //s
	pthread_mutex_t	*lock_print;
	pthread_mutex_t	*lock_dinner;
}	t_data;

typedef struct s_philo
{
	long				name;
	long				meals;
	long			lastsupper;
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*lock_supper;
	pthread_mutex_t	*lock_meals;
	t_data			*data;
}	t_philo;

int		ft_isspace(int c);
int		ft_isdigit(int c);
long	ft_atol(char *str);

long    timenow(long firststamp);
long	timestamp(void);
void	msleep(int time_in_ms);  //ok verificar se não devo proteger essa função com mutex
void	set_meals(t_philo *philo);
void	set_lastsupper(t_philo *philo);
int	get_lastsupper(t_philo *philo);
int	get_meals(t_philo *philo);

#endif
