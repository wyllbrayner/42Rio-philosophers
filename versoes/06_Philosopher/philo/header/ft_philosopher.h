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

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
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
typedef pthread_t		t_pth;

typedef struct s_data
{
	int		ret;
	int		dinner_is_over;
	long	nbr_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	must_eat;
	long	firststamp;
	t_mutex	lock_print;
	t_mutex	lock_dinner;
}	t_data;

typedef struct s_philo
{
	long	id;
	long	meals;
	long	t_last_meal;
	t_pth	th;
	t_mutex	*fork_left;
	t_mutex	*fork_right;
	t_mutex	lock_t_last_meal;
	t_mutex	lock_meals;
	t_data	*data;
}	t_philo;

int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_dinner_is_over(t_philo *phi);
long	ft_atol(char *str);
void	ft_error(t_data *data);
long	ft_timenow(long firststamp);
long	ft_timestamp(void);
//void	ft_msleep(long time_in_ms);
void	ft_msleep(t_philo *phi, int action);
long	ft_get_meals(t_philo *phi);
long	ft_get_last_meal(t_philo *phi);
void	ft_set_meals(t_philo *phi);
void	ft_set_last_meal(t_philo *phi);
void	ft_print_action(t_philo *phi, int action);
void	*ft_actions(void *ptr);
void	*ft_monitor(void *ptr);
t_philo	*ft_start_philosophers(long nbr_phi, t_philo *phi);
t_data	*ft_check_input(int argc, char **argv, t_data *dt);
#endif
