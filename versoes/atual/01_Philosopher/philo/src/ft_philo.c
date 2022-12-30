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

void	init_data(int argc, char **argv, t_data *data);
t_data	*init_forks(t_data *data, t_mutex **forks);
t_data	*init_philos(t_data *data, t_mutex **forks, t_philo **philos);
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
		init_data(argc, argv, &data);
		init_forks(&data, &forks);
		if (data.ret < 0)
		{
			printf("Failed to alloc forks!\n");		
			exit_philo (data.number_of_philos, &data, forks, philos);
		}
		init_philos(&data, &forks, &philos);
		if (data.ret < 0)
		{
			printf("Failed to alloc philosophers!\n");
			exit_philo (data.number_of_philos, &data, forks, philos);
		}
		start_philosophers(data.number_of_philos, philos);
		deinit_philo(data.number_of_philos, &data, forks, philos);
	}
	return (0);
}

void	init_data(int argc, char **argv, t_data *data) //ok
{
	data->number_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->times_must_eat = -1;
	if (argc == 6)
		data->times_must_eat = ft_atol(argv[5]);
	if (data->number_of_philos == 1)
		data->alone = 1;
	else
		data->alone = 0;
	data->dinner_is_over = 0;
	data->firststamp = 0;
	pthread_mutex_init(&data->lock_print, NULL);
	pthread_mutex_init(&data->lock_dinner, NULL);
}

t_data	*init_forks(t_data *data, t_mutex **forks)
{
	int	i;

	*forks = (t_mutex *)malloc(sizeof(t_mutex) * data->number_of_philos);
	if (*forks == NULL)
	{
		data->ret = -4;
		return (data);
	}
	i = -1;
	while (++i < data->number_of_philos)
		pthread_mutex_init(&(*forks)[i], NULL);
	return (data);
}

t_data	*init_philos(t_data *data, t_mutex **forks, t_philo **philos)
{
	int	i;

	*philos = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philos);
	if (*philos == NULL)
	{
		data->ret = -5;
		return (data);
	}
	i = -1;
	while (++i < data->number_of_philos)
	{
		(*philos)[i].fork_right = &(*forks)[i];
		(*philos)[i].fork_left = &(*forks)[i + 1];
		(*philos)[i].name = i + 1;
		(*philos)[i].meals = 0;
		(*philos)[i].lastsupper = 0;
		(*philos)[i].data = data;
		pthread_mutex_init(&(*philos)[i].lock_supper, NULL);
		pthread_mutex_init(&(*philos)[i].lock_meals, NULL);
	}
	(*philos)[--i].fork_left = &(*forks)[0];
	return (data);
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
		pthread_mutex_destroy(&philos[i].lock_supper);
		pthread_mutex_destroy(&philos[i].lock_meals);
	}
	pthread_mutex_destroy(&data->lock_print);
	pthread_mutex_destroy(&data->lock_dinner);
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
		pthread_mutex_destroy(&philos[i].lock_supper);
		pthread_mutex_destroy(&philos[i].lock_meals);
	}
	pthread_mutex_destroy(&data->lock_print);
	pthread_mutex_destroy(&data->lock_dinner);
	free(forks);
	free(philos);
	exit(EXIT_FAILURE); //confirmar que pode usar esta funcao
}
