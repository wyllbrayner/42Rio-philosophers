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

void	*actions(void *ptr);
static void	*go_eat_alone(t_philo *philo); //ok
static void	go_eat(t_philo *philo);
static void	go_sleep(t_philo *philo);
static void	go_think(t_philo *philo);
int	dinner_is_over(t_philo *philo);
void	finish_dinner(t_philo *philo);
static int	all_philos_ate(t_philo *philos);
void	*philosopher_monitor(void *ptr);
void	print_action(t_philo *philo, int action);

int	start_philosophers(int n, t_philo *philos) // ok
{
	int			i;
	pthread_t	monitor_thread;

	i = -1;
	philos->data->firststamp = timestamp();
	while (++i < n)
		pthread_create(&philos[i].thread, NULL, &actions, &philos[i]);
	pthread_create(&monitor_thread, NULL, &philosopher_monitor, philos);
	i = -1;
	while (++i < n)
		pthread_join(philos[i].thread, NULL);
	pthread_join(monitor_thread, NULL);
	return (0);
}

void	*actions(void *ptr) // ok
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->name % 2)
		msleep(5);
	if (philo->data->alone)
		return (go_eat_alone(philo));
	while (!dinner_is_over(philo))
	{
		go_eat(philo);
		if (get_meals(philo) == philo->data->times_must_eat)
			return (NULL);
		go_sleep(philo);
		go_think(philo);
	}
	return (NULL);
}

static void	*go_eat_alone(t_philo *philo) //ok
{
	pthread_mutex_lock(philo->fork_right);
	print_action(philo, TOOK_A_FORK);
	pthread_mutex_unlock(philo->fork_right);
	return (NULL);
}

static void	go_eat(t_philo *philo) //ok
{
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(philo->fork_left);
	if (dinner_is_over(philo))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return ;
	}
	print_action(philo, TOOK_A_FORK);
	print_action(philo, TOOK_A_FORK);
	print_action(philo, EATING);
	set_lastsupper(philo);
	msleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	set_meals(philo);
}

static void	go_sleep(t_philo *philo) // ok
{
	print_action(philo, SLEEPING);
	msleep(philo->data->time_to_sleep);
}

static void	go_think(t_philo *philo) // ok
{
	print_action(philo, THINKING);
	usleep(500);
}

int	dinner_is_over(t_philo *philo) // ok
{
	int	dinner_is_over;

	pthread_mutex_lock(philo->data->lock_dinner);
	dinner_is_over = 0;
	if (philo->data->dinner_is_over)
		dinner_is_over = philo->data->dinner_is_over;
	pthread_mutex_unlock(philo->data->lock_dinner);
	return (dinner_is_over);
}

void	finish_dinner(t_philo *philo) // ok
{
	pthread_mutex_lock(philo->data->lock_dinner);
	philo->data->dinner_is_over = 1;
	pthread_mutex_unlock(philo->data->lock_dinner);
}

void	*philosopher_monitor(void *ptr) //ok
{
	int		i;
	long	current_time;
	long	time_to_die;
	t_philo	*philos;

	philos = (t_philo *)ptr;
	time_to_die = philos->data->time_to_die;
	while (!all_philos_ate(philos))
	{
		i = -1;
		while (++i < philos->data->number_of_philos)
		{
			current_time = timenow(philos->data->firststamp);
			if ((current_time - get_lastsupper(&philos[i])) > time_to_die)
			{
				finish_dinner(&philos[i]);
				print_action(&philos[i], DIED);
				return (NULL);
			}
		}
		msleep(1);
	}
	return (NULL);
}

static int	all_philos_ate(t_philo *philos) // ok
{
	int	i;
	int	had_dinner;

	had_dinner = 0;
	i = -1;
	while (++i < philos->data->number_of_philos)
	{
		if (get_meals(&philos[i]) == philos[i].data->times_must_eat)
			had_dinner++;
	}
	if (had_dinner == philos->data->number_of_philos)
		return (1);
	return (0);
}

void	print_action(t_philo *philo, int action) // ok
{
	long	current_time;

	pthread_mutex_lock(philo->data->lock_print);
	current_time = timenow(philo->data->firststamp);
	if (action == TOOK_A_FORK && !dinner_is_over(philo))
		printf("%ld %ld has taken a fork\n", current_time, philo->name);
	else if (action == EATING && !dinner_is_over(philo))
		printf("%ld %ld is eating\n", current_time, philo->name);
	else if (action == SLEEPING && !dinner_is_over(philo))
		printf("%ld %ld is sleeping\n", current_time, philo->name);
	else if (action == THINKING && !dinner_is_over(philo))
		printf("%ld %ld is thinking\n", current_time, philo->name);
	else if (action == DIED)
		printf("%ld %ld died\n", current_time, philo->name);
	pthread_mutex_unlock(philo->data->lock_print);
}