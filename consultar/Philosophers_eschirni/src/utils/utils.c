/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:14:11 by eschirni          #+#    #+#             */
/*   Updated: 2022/03/19 17:36:09 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	print_help(void)
{
	write(2, CYAN, ft_strclen(CYAN, '\0'));
	write(2, "Usage: [number of philosophers] ", 32);
	write(2, "[time to die] [time to eat] [time to sleep] ", 44);
	write(2, "[number of meals a philosopher has to eat]\n", 43);
	return (ft_exit("wrong number of arguments!"));
}

void	philosophy(void)
{
	write(1, CYAN "\n\"", 2 + ft_strclen(CYAN, '\0'));
	if (get_time() % 9 == 0)
	{
		write(1, "If there's anything more important than my ego around,", 54);
		write(1, " I want it caught and shot now.", 31);
	}
	else if (get_time() % 9 == 1)
	{
		write(1, "For a moment, nothing happened. Then, ", 38);
		write(1, "after a second or so, nothing continued to happen.", 50);
	}
	else if (get_time() % 9 == 2)
		write(1, "I'd far rather be happy than right any day.", 43);
	else if (get_time() % 9 == 3)
		write(1, "Time is an illusion. Lunchtime doubly so.", 41);
	else if (get_time() % 9 == 4)
		write(1, "Don't Panic.", 12);
	else if (get_time() % 9 == 5)
		write(1, "I never could get the hang of Thursdays.", 40);
	else if (get_time() % 9 == 7)
		write(1, "Ford... you're turning into a penguin. Stop it.", 47);
	else
		write(1, "So long, and thanks for all the fish.", 37);
	write(1, "\"\n\n", 3);
	write(1, RESETCOLOR, ft_strclen(RESETCOLOR, '\0'));
}

void	msleep(long long time)
{
	long long	before;
	long long	now;

	before = get_time();
	now = before;
	while (now - before < time)
	{
		usleep(100);
		now = get_time();
	}
}

long long	get_time(void)
{
	struct timeval	time;
	long			sec;

	if (gettimeofday(&time, NULL) == -1)
	{
		ft_exit("Error while reading the time");
		return (-1);
	}
	sec = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (sec);
}

void	ft_write_action(char *action, t_philo *philo)
{
	printf("%lld %d %s\n", get_time() - philo->start, philo->id, action);
}
