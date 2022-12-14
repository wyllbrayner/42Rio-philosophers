/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:42:12 by eschirni          #+#    #+#             */
/*   Updated: 2022/03/23 11:58:43 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	action(t_rules *rules, t_philo *philo, long long wait, char *s)
{
	pthread_mutex_lock(&rules->mutex);
	if (rules->end == true)
	{
		pthread_mutex_unlock(&rules->mutex);
		return ;
	}
	ft_write_action(s, philo);
	if (get_time() - philo->last_meal + wait > rules->ttd)
	{
		if (rules->end == false)
		{
			rules->end = true;
			msleep(rules->ttd - (get_time() - philo->last_meal));
			philo->dead = true;
			pthread_mutex_unlock(&rules->mutex);
			return ;
		}
	}
	else
	{
		pthread_mutex_unlock(&rules->mutex);
		msleep(wait);
	}
	return ;
}

static bool	get_forks(t_rules *rules, t_philo *philo, int id)
{
	pthread_mutex_lock(&rules->mutex);
	if (get_time() - philo->last_meal >= rules->ttd && rules->end == false)
	{
		rules->end = true;
		philo->dead = true;
	}
	pthread_mutex_unlock(&rules->mutex);
	if (rules->forks->locked[id] == false)
	{
		rules->forks->locked[id] = true;
		pthread_mutex_lock(&rules->forks->forks[id]);
		philo->forks++;
		if (rules->end == true)
			return (false);
		ft_write_action("picked up a fork", philo);
	}
	return (true);
}

static void	eat(t_rules *rules, t_philo *philo, int next_id)
{
	int	id;

	id = philo->id - 1;
	while (rules->end == false)
	{
		if (get_forks(rules, philo, id) == false)
			break ;
		if (get_forks(rules, philo, next_id) == false)
			break ;
		if (philo->forks == 2)
		{
			philo->last_meal = get_time();
			action(rules, philo, rules->tte, "is eating");
			break ;
		}
	}
	rules->forks->locked[id] = false;
	rules->forks->locked[next_id] = false;
	philo->forks = 0;
	pthread_mutex_unlock(&rules->forks->forks[id]);
	pthread_mutex_unlock(&rules->forks->forks[next_id]);
}

static void	end_of_routine(t_rules *rules, t_philo *philo)
{
	usleep(500);
	
	pthread_mutex_lock(&rules->mutex);
	rules->philo_id--;
	pthread_mutex_unlock(&rules->mutex);
	while (rules->philo_id != 0)
		continue;
	if (philo->dead == true)
		ft_write_action("died", philo);
	rules->end = true;
}

void	routine(t_rules *rules, t_philo *philo)
{
	int	next_id;

	next_id = philo->id;
	if (philo->id == rules->philo_id)
		next_id = 0;
	if (next_id % 2 == 1)
	{
		action(rules, philo, rules->tts, "is sleeping");
		action(rules, philo, 0, "is thinking");
	}
	while (rules->end == false && rules->meals > 0)
	{
		eat(rules, philo, next_id);
		philo->meals++;
		if (rules->count_meals == true && philo->meals >= rules->meals)
			break ;
		action(rules, philo, rules->tts, "is sleeping");
		action(rules, philo, 0, "is thinking");
	}
	end_of_routine(rules, philo);
}
