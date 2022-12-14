/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:06:05 by eschirni          #+#    #+#             */
/*   Updated: 2022/03/19 18:51:34 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static bool	set_rules(int argc, char **argv, t_rules *rules)
{
	if (pthread_mutex_init(&rules->mutex, NULL) != 0)
	{
		ft_exit("mutex error!");
		return (false);
	}
	rules->philos = ft_atoi(argv[1]);
	if (rules->philos == 0)
	{
		ft_exit("There must be at least one philosopher!");
		return (false);
	}
	rules->ttd = ft_atoi(argv[2]);
	rules->tte = ft_atoi(argv[3]);
	rules->tts = ft_atoi(argv[4]);
	rules->count_meals = false;
	rules->end = false;
	rules->created = 0;
	rules->meals = 1;
	if (argc > 5)
	{
		rules->count_meals = true;
		rules->meals = ft_atoi(argv[5]);
	}
	return (true);
}

static bool	create_forks_struct(t_rules *rules)
{
	rules->forks = malloc(rules->philos * sizeof(t_forks));
	if (rules->forks == NULL)
	{
		ft_exit("allocation error!");
		return (false);
	}
	rules->forks->forks = malloc(rules->philos * sizeof(pthread_mutex_t));
	if (rules->forks->forks == NULL)
	{
		ft_exit("allocation error!");
		return (false);
	}
	rules->forks->locked = malloc(rules->philos * sizeof(bool));
	if (rules->forks->locked == NULL)
	{
		ft_exit("allocation error!");
		return (false);
	}
	return (true);
}

static bool	create_forks(t_rules *rules)
{
	int	i;

	if (create_forks_struct(rules) == false)
		return (false);
	i = 0;
	while (i < rules->philos)
	{
		if (pthread_mutex_init(&rules->forks->forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&rules->forks->forks[i]);
			}
			free(rules->forks->locked);
			free(rules->forks->forks);
			ft_exit("mutex error!");
			return (false);
		}
		rules->forks->locked[i] = false;
		i++;
	}
	return (true);
}

t_rules	*read_input(int argc, char **argv)
{
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (rules == NULL)
	{
		ft_exit("allocation error!");
		return (NULL);
	}
	if (ft_isnum(argc - 1, argv) == false)
	{
		free(rules);
		ft_exit("Invalid input!");
		return (NULL);
	}
	if (set_rules(argc, argv, rules) == false)
	{
		free(rules);
		return (NULL);
	}
	if (create_forks(rules) == false)
	{
		free(rules);
		return (NULL);
	}
	return (rules);
}

int	check(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '\0')
			return (ft_exit("empty string!"));
		else if (ft_atoi(argv[i]) > INT_MAX)
			return (ft_exit("number larger than max int value!"));
		i++;
	}
	return (EXIT_SUCCESS);
}
