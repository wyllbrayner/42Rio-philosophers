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

void	start_philosophers(int n, t_philo *philos);

void	init_args(int argc, char **argv, t_data *data);
void	init_data(t_data *data, pthread_mutex_t **forks, t_philo **philos);
void	init_forks(int n, t_data *data, t_mutex **forks, t_philo **philos);
void	init_philos(int n, t_data *data, t_mutex **forks, t_philo **philos);
void	deinit_philo(int n, t_data *data, t_mutex *forks, t_philo *philos);
void	exit_philo(int n, t_data *data, t_mutex *forks, t_philo *philos);

int main(int argc, char **argv) // ok
{
	t_data	data;
	t_mutex	*forks;
	t_philo	*philos;

	ft_check_input(argc, argv, &data);
	if (data.ret >= 0)
	{
//		printf("data ret: %d\n", data.ret);
		init_args(argc, argv, &data);
		init_data(&data, &forks, &philos);
		init_forks(data.number_of_philos, &data, &forks, &philos);
		init_philos(data.number_of_philos, &data, &forks, &philos);
		start_philosophers(data.number_of_philos, philos);
		deinit_philo(data.number_of_philos, &data, forks, philos);
	}
	return (0);
}

void	init_args(int argc, char **argv, t_data *data) //ok
{
	data->number_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->times_must_eat = -1;
	if (argc == 6)
		data->times_must_eat = ft_atol(argv[5]);
}

void	init_data(t_data *data, pthread_mutex_t **forks, t_philo **philos)
{
	*forks = NULL;
	*philos = NULL;
	if (data->number_of_philos == 1)
		data->alone = 1;
	else
		data->alone = 0;
	data->dinner_is_over = 0;
	data->firststamp = 0;
	data->lock_print = (t_mutex *)malloc(sizeof(t_mutex) * 1);
	data->lock_dinner = (t_mutex *)malloc(sizeof(t_mutex) * 1);
	if (data->lock_print == NULL || data->lock_dinner == NULL)
	{
		printf("Failed to alloc mutex!\n");
		exit_philo (0, data, *forks, *philos);
	}
	pthread_mutex_init(data->lock_print, NULL);
	pthread_mutex_init(data->lock_dinner, NULL);
}

void	init_forks(int n, t_data *data, t_mutex **forks, t_philo **philos)
{
	int	i;

	*forks = (t_mutex *)malloc(sizeof(t_mutex) * n);
	if (*forks == NULL)
	{
		printf("Failed to alloc forks!\n");
		exit_philo (n, data, *forks, *philos);
	}
	i = -1;
	while (++i < n)
		pthread_mutex_init(&(*forks)[i], NULL);
}

void	init_philos(int n, t_data *data, t_mutex **forks, t_philo **philos)
{
	int	i;

	*philos = (t_philo *)malloc(sizeof(t_philo) * n);
	if (*philos == NULL)
	{
		printf("Failed to alloc philosophers!\n");
		exit_philo (n, data, *forks, *philos);
	}
	i = -1;
	while (++i < n)
	{
		(*philos)[i].fork_right = &(*forks)[i];
		(*philos)[i].fork_left = &(*forks)[i + 1];
		(*philos)[i].lock_supper = (t_mutex *)malloc(sizeof(t_mutex) * 1);
		(*philos)[i].lock_meals = (t_mutex *)malloc(sizeof(t_mutex) * 1);
		(*philos)[i].name = i + 1;
		(*philos)[i].meals = 0;
		(*philos)[i].lastsupper = 0;
		(*philos)[i].data = data;
		pthread_mutex_init((*philos)[i].lock_supper, NULL);
		pthread_mutex_init((*philos)[i].lock_meals, NULL);
	}
	(*philos)[--i].fork_left = &(*forks)[0];
}

void	deinit_philo(int n, t_data *data, t_mutex *forks, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < n && forks)
		pthread_mutex_destroy(&forks[i]);
	i = -1;
	while (++i < n && philos)
	{
		if (philos[i].lock_supper)
			pthread_mutex_destroy(philos[i].lock_supper);
		if (philos[i].lock_meals)
			pthread_mutex_destroy(philos[i].lock_meals);
		free(philos[i].lock_supper);
		free(philos[i].lock_meals);
	}
	if (data->lock_print)
		pthread_mutex_destroy(data->lock_print);
	if (data->lock_dinner)
		pthread_mutex_destroy(data->lock_dinner);
	free(data->lock_print);
	free(data->lock_dinner);
	free(forks);
	free(philos);
}

void	exit_philo(int n, t_data *data, t_mutex *forks, t_philo *philos) //ok
{
	int	i;

	i = -1;
	while (++i < n && forks)
		pthread_mutex_destroy(&forks[i]);
	i = -1;
	while (++i < n && philos)
	{
		if (philos[i].lock_supper)
			pthread_mutex_destroy(philos[i].lock_supper);
		if (philos[i].lock_meals)
			pthread_mutex_destroy(philos[i].lock_meals);
		free(philos[i].lock_supper);
		free(philos[i].lock_meals);
	}
	if (data->lock_print)
		pthread_mutex_destroy(data->lock_print);
	if (data->lock_dinner)
		pthread_mutex_destroy(data->lock_dinner);
	free(data->lock_print);
	free(data->lock_dinner);
	free(forks);
	free(philos);
	exit(EXIT_FAILURE); //confirmar que pode usar esta funcao
}
