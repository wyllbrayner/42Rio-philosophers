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

// cc ft_testes.c -Wall -Werror -Wextra -pthread -o test && ./test

#include "../header/ft_philosopher.h"

void    ft_init_struct(char **argv, t_philo *t_ph)
{

    t_ph->nbr_philo = ft_atol(argv[1]);
    t_ph->nbr_fork = t_ph->nbr_philo;
    t_ph->t_to_die = ft_atol(argv[2]);
    t_ph->t_to_eat = ft_atol(argv[3]);
    t_ph->t_to_sleep = ft_atol(argv[4]);
    if (argv[5])
        t_ph->t_must_eat = ft_atol(argv[5]);
    else
        t_ph->t_must_eat = 0;
}

t_philo ft_run_philosophers(t_philo *t_ph)
{

}


long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

t_philo ft_philosophers(int argc, char **argv)
{
    t_philo t_ph;

    t_ph.ret = 0;
    ft_check_input(argc, argv, &t_ph);
    if (t_ph.ret < 0)
	{
		if (t_ph.ret == -1)
			ft_putstr_fd("Error: Invalid number of arguments.\n", 1);
		else
			ft_putstr_fd("Error: Invalid arguments.\n", 1);
        return (t_ph);
	}
    ft_init_struct(argv, &t_ph);
	ft_run_philosophers(&t_ph);
    return (t_ph);
}

int main(int argc, char **argv)
{
    t_philo t_ph_main;

    printf("Entrou na main e vai chamar a philosopher\n");
    t_ph_main = ft_philosophers(argc, argv);
    printf("Na main retornou da philosopher\n");
    printf("retornou          : %d\n",t_ph_main.ret);
    printf("qtd of philo      : %ld\n",t_ph_main.nbr_philo);
    printf("qtd of fork       : %ld\n",t_ph_main.nbr_fork);
    printf("qtd of t_must_eat : %ld\n",t_ph_main.t_must_eat);
    printf("qtd of t_to_die   : %d\n",t_ph_main.t_to_die);
    printf("qtd of t_to_eat   : %d\n",t_ph_main.t_to_eat);
    printf("qtd of t_to_sleep : %d\n",t_ph_main.t_to_sleep);
    return (0);
}