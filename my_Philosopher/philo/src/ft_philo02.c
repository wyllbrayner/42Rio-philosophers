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

pthread_mutex_t mutex01;

void    ft_init_struct(char **argv, t_setup *t_ph)
{
    t_ph->nbr_philo = ft_atol(argv[1]);
    t_ph->nbr_fork = t_ph->nbr_philo;
    t_ph->t_to_die = ft_atol(argv[2]);
    t_ph->t_to_eat = ft_atol(argv[3]);
    t_ph->t_to_sleep = ft_atol(argv[4]);
    if (argv[5])
        t_ph->must_eat = ft_atol(argv[5]);
    else
        t_ph->must_eat = 0;
}


long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void *ft_routine(void *arg)
{
    int i;
    t_thinker nbr_philo = *(t_thinker *)arg;
    i = 0;
    while (i < 10)
    {
    pthread_mutex_lock(&mutex01);
        printf("O philosopho %d está comendo %d\n", nbr_philo.philo_n, i);
    pthread_mutex_unlock(&mutex01);
    pthread_mutex_lock(&mutex01);
        printf("O philosopho %d está dormindo %d\n", nbr_philo.philo_n, i);
    pthread_mutex_unlock(&mutex01);
    pthread_mutex_lock(&mutex01);
        printf("O philosopho %d está pensando %d\n", nbr_philo.philo_n, i);
    pthread_mutex_unlock(&mutex01);
        i++;        
    }
    pthread_mutex_lock(&mutex01);
    printf("O philosopho %d terminou\n", nbr_philo.philo_n);
    pthread_mutex_unlock(&mutex01);
    free(arg);
    arg = NULL;
    return (0);
}

t_setup *ft_run_philosophers(t_setup *t_ph)
{

    int i;
    t_thinker *tmp;
//    int *nbr;
    pthread_t   tmp_th[t_ph->nbr_philo];

    i = 0;
    pthread_mutex_init(&mutex01, NULL);
    while (i < t_ph->nbr_philo)
    {
        tmp = malloc(sizeof(t_thinker) * 1);
        if (!tmp)
            return (t_ph);
//        nbr = malloc(sizeof(int) * 1);
//        if (!nbr)
//            return (t_ph);
//        *nbr = i + 1;
        tmp->philo_n = i + 1;
        if (pthread_create(&tmp_th[i], NULL, &ft_routine, tmp) != 0)
        {
            t_ph->ret = -4;
            return (t_ph);
        }    
        i++;
    }
    i = 0;
    while (i < t_ph->nbr_philo)
    {
        if (pthread_join(tmp_th[i], NULL) != 0)
        {
            t_ph->ret = -5;
            return (t_ph);
        }
        i++;
    }
    pthread_mutex_destroy(&mutex01);
    return (t_ph);
}

t_setup ft_philosophers(int argc, char **argv)
{
    t_setup t_ph;

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
    t_setup t_ph_main;

    t_ph_main = ft_philosophers(argc, argv);
//    printf("Na main retornou da philosopher\n");
//    printf("retornou          : %d\n",t_ph_main.ret);
//    printf("qtd of philo      : %ld\n",t_ph_main.nbr_philo);
//    printf("qtd of fork       : %ld\n",t_ph_main.nbr_fork);
//    printf("qtd of must_eat   : %ld\n",t_ph_main.must_eat);
//    printf("qtd of t_to_die   : %d\n",t_ph_main.t_to_die);
//    printf("qtd of t_to_eat   : %d\n",t_ph_main.t_to_eat);
//    printf("qtd of t_to_sleep : %d\n",t_ph_main.t_to_sleep);
    return (0);
}