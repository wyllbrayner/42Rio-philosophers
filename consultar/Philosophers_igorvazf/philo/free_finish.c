/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvaz-fe <igvaz-fe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:58:45 by igvaz-fe          #+#    #+#             */
/*   Updated: 2022/03/21 21:08:14 by igvaz-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_dinner(t_philo *philo, t_setup *setup)
{
	int	i;

	i = 0;
	while (i < setup->n_philos)
	{
		pthread_mutex_destroy(&setup->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&setup->print_locker);
	free(setup->forks);
	free(philo);
}
