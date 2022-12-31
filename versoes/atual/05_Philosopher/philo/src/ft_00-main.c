/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_00-main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/12/30 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_philosopher.h"

static t_data	*ft_init_structures(t_data *dt, t_mutex **forks, t_philo **ph);
static void		ft_init_data(int argc, char **argv, t_data *dt);
static void		ft_init_structures_aux(t_data *dt, t_mutex **forks, \
		t_philo **phi);
static void		ft_destroy_structures(t_data *dt, t_mutex *forks, t_philo *phi);

int	main(int argc, char **argv)
{
	t_data	dt;
	t_mutex	*forks;
	t_philo	*phi;

	forks = NULL;
	phi = NULL;
	ft_check_input(argc, argv, &dt);
	if (dt.ret < 0)
		ft_error(&dt);
	else
	{
		ft_init_data(argc, argv, &dt);
		ft_init_structures(&dt, &forks, &phi);
		if (dt.ret < 0)
			ft_error(&dt);
		else
			ft_start_philosophers(dt.nbr_philos, phi);
		ft_destroy_structures(&dt, forks, phi);
	}
	return (0);
}

static void	ft_init_data(int argc, char **argv, t_data *dt)
{
	dt->nbr_philos = ft_atol(argv[1]);
	dt->time_to_die = ft_atol(argv[2]);
	dt->time_to_eat = ft_atol(argv[3]);
	dt->time_to_sleep = ft_atol(argv[4]);
	dt->must_eat = -1;
	if (argc == 6)
		dt->must_eat = ft_atol(argv[5]);
	dt->dinner_is_over = FALSE;
	dt->firststamp = 0;
	pthread_mutex_init(&dt->lock_print, NULL);
	pthread_mutex_init(&dt->lock_dinner, NULL);
}

static t_data	*ft_init_structures(t_data *dt, t_mutex **forks, t_philo **phi)
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
	*phi = (t_philo *)malloc(sizeof(t_philo) * dt->nbr_philos);
	if (*phi == NULL)
	{
		dt->ret = -5;
		return (dt);
	}
	ft_init_structures_aux(dt, forks, phi);
	return (dt);
}

static void	ft_init_structures_aux(t_data *dt, t_mutex **forks, t_philo **phi)
{
	long	i;

	i = -1;
	while (++i < dt->nbr_philos)
	{
		(*phi)[i].fork_right = &(*forks)[i];
		if (i == (dt->nbr_philos - 1))
			(*phi)[i].fork_left = &(*forks)[0];
		else
			(*phi)[i].fork_left = &(*forks)[i + 1];
		(*phi)[i].id = i + 1;
		(*phi)[i].meals = 0;
		(*phi)[i].t_last_meal = 0;
		(*phi)[i].data = dt;
		pthread_mutex_init(&(*phi)[i].lock_t_last_meal, NULL);
		pthread_mutex_init(&(*phi)[i].lock_meals, NULL);
	}
}

static void	ft_destroy_structures(t_data *dt, t_mutex *forks, t_philo *phi)
{
	long	i;

	i = -1;
	while ((++i < dt->nbr_philos) && forks)
		pthread_mutex_destroy(&forks[i]);
	i = 0;
	while ((i < dt->nbr_philos) && phi)
	{
		pthread_mutex_destroy(&phi[i].lock_t_last_meal);
		pthread_mutex_destroy(&phi[i].lock_meals);
		i++;
	}
	pthread_mutex_destroy(&dt->lock_print);
	pthread_mutex_destroy(&dt->lock_dinner);
	if (forks)
	{
		free(forks);
		forks = NULL;
	}
	if (phi)
	{
		free(phi);
		phi = NULL;
	}
}
