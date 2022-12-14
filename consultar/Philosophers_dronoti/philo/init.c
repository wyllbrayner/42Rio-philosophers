/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:34:38 by bkael             #+#    #+#             */
/*   Updated: 2021/09/16 16:35:03 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	long long		num;

	i = 0;
	num = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			return (-1);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		if (num > 2147483647)
			return (-1);
		i++;
	}
	if (nptr[i] != '\0')
		return (-1);
	return (num);
}

int	ft_init_arg(t_philo *philo, int argc, char **argv)
{
	philo->number_of_philo = ft_atoi(argv[1]);
	philo->die = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->number_of_eats = ft_atoi(argv[5]);
	else
		philo->number_of_eats = 0;
	if (argc == 6 && philo->number_of_eats < 1)
		return (1);
	if (philo->number_of_philo < 1 || philo->die < 1 || philo->sleep < 1
		|| philo->eat < 1 || philo->number_of_philo > 200)
		return (1);
	return (0);
}

int	ft_malloc_philo(t_philo *philo)
{
	philo->persons = malloc(sizeof(t_person) * philo->number_of_philo);
	if (!philo->persons)
		return (1);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->number_of_philo);
	if (!philo->forks)
	{
		free(philo->persons);
		return (1);
	}
	return (0);
}

int	ft_init_persons(t_philo *philo)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&philo->print, NULL))
		return (1);
	while (i < philo->number_of_philo)
	{
		philo->persons[i].i = i;
		philo->persons[i].times_eats = 0;
		philo->persons[i].left = i;
		if (i + 1 < philo->number_of_philo)
			philo->persons[i].right = i + 1;
		else
			philo->persons[i].right = 0;
		if (pthread_mutex_init(&philo->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_all(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->persons)
		free(philo->persons);
	if (philo->forks)
	{
		while (i < philo->number_of_philo)
		{
			pthread_mutex_destroy(&philo->forks[i]);
			i++;
		}
		pthread_mutex_destroy(&philo->print);
		free(philo->forks);
	}
}
