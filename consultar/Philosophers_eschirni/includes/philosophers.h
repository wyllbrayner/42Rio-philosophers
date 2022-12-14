/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:04:04 by eschirni          #+#    #+#             */
/*   Updated: 2022/03/21 16:05:47 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//libs
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

//colors
# define RED "\033[0;31m"
# define CYAN "\033[0;36m"
# define RESETCOLOR "\033[0m"

//structs
typedef struct s_rules
{
	bool			count_meals;
	bool			end;
	int				created;
	int				philos;
	int				philo_id;
	int				meals;
	long long		ttd;
	long long		tte;
	long long		tts;
	long long		start;
	pthread_mutex_t	mutex;
	struct s_forks	*forks;
}				t_rules;

typedef struct s_philo
{
	bool		dead;
	int			forks;
	int			id;
	int			meals;
	long long	last_meal;
	long long	start;
}				t_philo;

typedef struct s_forks
{
	bool			*locked;
	pthread_mutex_t	*forks;
}				t_forks;

//utils
int			print_help(void);
long		ft_atoi(const char *str);
int			ft_exit(char *error);
bool		ft_isnum(int size, char **s);
void		ft_write_action(char *action, t_philo *philo);
void		msleep(long long time);
void		philosophy(void);
size_t		ft_strclen(const char *s, char c);
long long	get_time(void);

//input
int			check(char **argv, int argc);
t_rules		*read_input(int argc, char **argv);

//routine
void		routine(t_rules *rules, t_philo *philo);

#endif
