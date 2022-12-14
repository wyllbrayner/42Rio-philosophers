/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvaz-fe <igvaz-fe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:43:04 by igvaz-fe          #+#    #+#             */
/*   Updated: 2022/03/21 23:04:17 by igvaz-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(t_setup *setup)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * setup->n_philos);
	while (i < setup->n_philos)
	{
		philo[i].philo_id = i + 1;
		philo[i].last_meal = get_time();
		philo[i].n_meals = 0;
		philo[i].left_fork = i;
		philo[i].right_fork = i + 1;
		philo[i].setup_philo = setup;
		pthread_mutex_init(&setup->forks[i], NULL);
		i++;
	}
	i--;
	philo[i].right_fork = 0;
	return (philo);
}

void	init_setup(t_setup *setup, int argc, char *argv[])
{
	setup->n_philos = ft_atoi(argv[1]);
	setup->time_to_die = ft_atoi(argv[2]);
	setup->time_to_eat = ft_atoi(argv[3]);
	setup->time_to_sleep = ft_atoi(argv[4]);
	setup->times_to_eat = 0;
	if (argc > 5)
		setup->times_to_eat = ft_atoi(argv[5]);
	setup->is_died = 0;
	setup->meals = 0;
	setup->forks = malloc(sizeof(pthread_mutex_t) * setup->n_philos);
	pthread_mutex_init(&setup->print_locker, NULL);
}

void	validation(int argc, char *argv[])
{
	int	i;
	int	j;

	while (0 < argc--)
	{
		i = 1;
		while (argv[i])
		{
			j = 0;
			while (argv[i][j])
			{
				if (!ft_isdigit(argv[i][j]) || ft_atol(argv[i]) > MAX_INT
					|| ft_atol(argv[i]) <= 0)
				{
					printf("Error: argv[%d] is not a valid input.\n", i);
					exit(1);
				}
				j++;
			}
			i++;
		}
	}
}

int	main(int argc, char *argv[])
{
	t_setup	setup;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments.\n");
		exit(1);
	}
	validation(argc, argv);
	init_setup(&setup, argc, argv);
	philo = init_philo(&setup);
	start_dinner(philo);
	finish_dinner(philo, &setup);
	return (0);
}
