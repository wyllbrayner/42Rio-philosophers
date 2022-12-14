/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:26:24 by bkael             #+#    #+#             */
/*   Updated: 2021/09/14 16:27:03 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_all_detach(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philo)
	{
		if (pthread_detach(philo->persons[i].thread))
			return (1);
		i++;
	}
	return (0);
}

void	ft_monitor(t_philo *philo, int i, int eat)
{
	while (1)
	{
		i = -1;
		eat = 0;
		while (++i < philo->number_of_philo)
		{
			if (ft_get_time() - philo->persons[i].timer > philo->die)
			{
				ft_print(philo, philo->persons[i].i + 1, "is died");
				return ;
			}
			if (philo->number_of_eats
				&& (philo->persons[i].times_eats >= philo->number_of_eats))
				eat++;
			if (eat >= philo->number_of_philo)
			{
				pthread_mutex_lock(&philo->print);
				ft_putendl_fd("Stop: All the philosophers ate", 1);
				return ;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_philo		philo;

	if (argc != 5 && argc != 6)
		return (ft_putendl_fd("Invalid number of arguments", 2));
	if (ft_init_arg(&philo, argc, argv))
		return (ft_putendl_fd("Invalid arguments", 2));
	if (ft_malloc_philo(&philo))
		return (ft_putendl_fd("Malloc error", 2));
	if (ft_init_persons(&philo))
	{
		ft_free_all(&philo);
		return (ft_putendl_fd("Mutex error", 2));
	}
	if (ft_pthreads_init(&philo))
	{
		ft_free_all(&philo);
		return (ft_putendl_fd("Threads error", 2));
	}
	ft_monitor(&philo, -1, 0);
	if (ft_all_detach(&philo))
		return (ft_putendl_fd("Detach error", 2));
	ft_free_all(&philo);
	return (0);
}
