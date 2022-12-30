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

static void	ft_init_data(int argc, char **argv, t_data *dt);
static t_data	*ft_init_structures(t_data *dt, t_mutex **forks, t_philo **philos);
static void	ft_init_structures_aux(t_data *dt, t_mutex **forks, t_philo **philos);
static void	ft_destroy_structures(t_data *dt, t_mutex *forks, t_philo *philos);

int main(int argc, char **argv)
{
	t_data	dt;
	t_mutex	*forks;
	t_philo	*philos;

	forks = NULL;
	philos = NULL;
	ft_check_input(argc, argv, &dt);
	if (dt.ret < 0)
		ft_error(&dt);
	else
	{
		ft_init_data(argc, argv, &dt);
		ft_init_structures(&dt, &forks, &philos);
		if (dt.ret < 0)
			ft_error(&dt);
		else
			ft_start_philosophers(dt.nbr_philos, philos);
		ft_destroy_structures(&dt, forks, philos);
	}
	return (0);
}

static void	ft_init_data(int argc, char **argv, t_data *dt)
{
	dt->nbr_philos = ft_atol(argv[1]);
	dt->time_to_die = ft_atol(argv[2]);
	dt->time_to_eat = ft_atol(argv[3]);
	dt->time_to_sleep = ft_atol(argv[4]);
	dt->times_must_eat = -1;
	if (argc == 6)
		dt->times_must_eat = ft_atol(argv[5]);
	if (dt->nbr_philos == 1)
		dt->alone = TRUE;
	else
		dt->alone = FALSE;
	dt->dinner_is_over = FALSE;
	dt->firststamp = 0;
	pthread_mutex_init(&dt->lock_print, NULL);
	pthread_mutex_init(&dt->lock_dinner, NULL);
}

static t_data	*ft_init_structures(t_data *dt, t_mutex **forks, t_philo **philos)
{
	long	i;

	*forks = (t_mutex *)malloc(sizeof(t_mutex) * dt->nbr_philos);
	if (*forks == NULL)
	{
		dt->ret = -4;
		return (dt);
	}
	i = -1;
	while (++i < dt->nbr_philos)
		pthread_mutex_init(&(*forks)[i], NULL);
	*philos = (t_philo *)malloc(sizeof(t_philo) * dt->nbr_philos);
	if (*philos == NULL)
	{
		dt->ret = -5;
		return (dt);
	}
	ft_init_structures_aux(dt, forks, philos);
	return (dt);
}

static void	ft_init_structures_aux(t_data *dt, t_mutex **forks, t_philo **philos)
{
	long	i;

	i = -1;
	while (++i < dt->nbr_philos)
	{
		(*philos)[i].fork_right = &(*forks)[i];
		if (i == (dt->nbr_philos - 1))
			(*philos)[i].fork_left = &(*forks)[0];
		else
			(*philos)[i].fork_left = &(*forks)[i + 1];
		(*philos)[i].name = i + 1;
		(*philos)[i].meals = 0;
		(*philos)[i].lastsupper = 0;
		(*philos)[i].data = dt;
		pthread_mutex_init(&(*philos)[i].lock_supper, NULL);
		pthread_mutex_init(&(*philos)[i].lock_meals, NULL);
	}
}

static void	ft_destroy_structures(t_data *dt, t_mutex *forks, t_philo *philos)
{
	long	i;

	i = -1;
	while ((++i < dt->nbr_philos) && forks)
		pthread_mutex_destroy(&forks[i]);
	i = 0;
	while ((i < dt->nbr_philos) && philos)
	{
		pthread_mutex_destroy(&philos[i].lock_supper);
		pthread_mutex_destroy(&philos[i].lock_meals);
		i++;
	}
	pthread_mutex_destroy(&dt->lock_print);
	pthread_mutex_destroy(&dt->lock_dinner);
	if (forks)
	{
		free(forks);
		forks = NULL;
	}
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
}