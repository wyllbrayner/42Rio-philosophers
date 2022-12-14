/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:23:41 by bkael             #+#    #+#             */
/*   Updated: 2021/09/14 16:26:08 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_person
{
	int			i;
	int			times_eats;
	int			timer;
	int			left;
	int			right;
	pthread_t	thread;
}				t_person;

typedef struct s_philo
{
	int				i;
	int				number_of_philo;
	int				die;
	int				eat;
	int				sleep;
	int				number_of_eats;
	int				start;
	t_person		*persons;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_philo;

int		ft_strlen(char *s);
int		ft_putendl_fd(char *s, int fd);
int		ft_atoi(const char *nptr);
int		ft_init_arg(t_philo *philo, int argc, char **argv);
int		ft_init_persons(t_philo *philo);
int		ft_malloc_philo(t_philo *philo);
void	ft_free_all(t_philo *philo);
int		ft_pthreads_init(t_philo *philo);
void	*ft_simulate(void *philo);
int		ft_get_time(void);
void	ft_wait(int wait);
void	ft_putnbr(int n);
void	ft_print(t_philo *philo, int id, char *str);
void	ft_eat(t_person *person, t_philo *philo);
void	ft_monitor(t_philo *philo, int i, int eat);
int		ft_all_detach(t_philo *philo);

#endif