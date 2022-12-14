/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structure_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:32:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/06 16:33:16 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/* /// Prints the values of the t_main_args structure
** void	ft_print_main_args(t_main_args *main_args)
** {
** 	printf("N Philos: [%d]\n", main_args->n_philos);
** 	printf("Time to die: [%d]\n", main_args->t_to_die);
** 	printf("Time to eat: [%d]\n", main_args->t_to_eat);
** 	printf("Time to sleep: [%d]\n", main_args->t_to_sleep);
** 	printf("Number to eat: [%d]\n", main_args->n_to_eat);
** }
*/

/* /// Prints the values of t_philo structure
** void	ft_print_philo(t_philo	*philo, int with_mutex)
** {
** 	if (with_mutex)
** 		pthread_mutex_lock(philo->displaying);
** 	printf("\n\n\n");
** 	printf("______________________________________________________________\n");
** 	printf("Philo number: [%d]\n", philo->philo_number);
** 	printf("Time to die: [%d]\n", philo->t_to_die);
** 	printf("Time to sleep: [%d]\n", philo->t_to_sleep);
** 	printf("Time to eat: [%d]\n", philo->t_to_eat);
** 	printf("N to eat: [%d]\n", philo->n_to_eat);
** 	printf("N_times_ate: [%d]\n", philo->n_times_ate);
** 	printf("Start time: [%d]\n", philo->start_time);
** 	printf("Current time: [%d]\n", philo->current_time);
** 	printf("N seconds without eating: [%d]\n", philo->time_last_time_ate);
** 	printf("Left fork address: [%p]\n", philo->left_fork);
** 	printf("Right fork address: [%p]\n", philo->right_fork);
** 	printf("\n_______________________________________________________________");
** 	printf("\n\n\n");
** 	if (with_mutex)
** 		pthread_mutex_unlock(philo->displaying);
** }
*/

/// Create a new t_main_args structure using malloc and set up its values.
/// Returns a NULL pointer if the malloc call fails
t_main_args	*ft_initialize_main_args_struct(int argc, char **argv)
{
	t_main_args	*ret;

	ret = malloc(sizeof(t_main_args));
	if (!ret)
		return (ft_puterr_ptr("Couldn't malloc a t_main_args"));
	ret->n_philos = (int)(ft_atol(argv[1]));
	ret->t_to_die = (int)(ft_atol(argv[2]));
	ret->t_to_eat = (int)(ft_atol(argv[3]));
	ret->t_to_sleep = (int)(ft_atol(argv[4]));
	ret->n_to_eat = 0;
	ret->dead = malloc(sizeof(int));
	if (!ret)
		return (ft_free(ret, "Failed to malloc \"dead\"", NULL));
	ret->displaying = (pthread_mutex_t *)ft_initialize_display_mutex();
	if (!(ret->displaying))
	{
		ft_free(ret->dead, NULL, NULL);
		return (ft_free(ret, NULL, NULL));
	}
	*(ret->dead) = 1;
	if (argc == 6)
		ret->n_to_eat = (int)(ft_atol(argv[5]));
	return (ret);
}

/// Creates a new t_philo structure and assigns its values
t_philo	*ft_initialize_philo(t_main_args *args, int n, t_philo **f)
{
	t_philo	*ret;

	ret = malloc(sizeof(t_philo));
	if (!ret)
		return (NULL);
	ret->philo_number = n;
	ret->ph_num = ft_itoa(n);
	if (!ret->ph_num)
		return (ft_free(ret, "Failed to itoa philo num", NULL));
	ret->t_to_die = args->t_to_die;
	ret->t_to_sleep = args->t_to_sleep;
	ret->t_to_eat = args->t_to_eat;
	ret->n_philos = args->n_philos;
	ret->n_to_eat = 0;
	if (args->n_to_eat)
		ret->n_to_eat = args->n_to_eat;
	ret->n_times_ate = 0;
	ret->start_time = 0;
	ret->current_time = 0;
	ret->time_last_time_ate = 0;
	ret->died = args->dead;
	if (!(n - 1))
		*f = ret;
	return (ret);
}

/// Frees to_free argument, displays error_msg argument and returns to_return
void	*ft_free(void *to_free, char *error_msg, void *to_return)
{
	free(to_free);
	if (error_msg)
		ft_puterr(error_msg);
	return (to_return);
}

/// Frees to_free argument, displays error_msg argument and returns to_return
int	ft_free_int_ret(void *to_free, char *error_msg, int to_return)
{
	free(to_free);
	if (error_msg)
		ft_puterr(error_msg);
	return (to_return);
}

/// Mallocs size bytes at *malloc_this memory adress
/// Returns the return value of malloc call
void	*ft_malloc(int size, void **malloc_this)
{
	if (!malloc_this)
		return (NULL);
	*malloc_this = malloc(size);
	return (malloc_this);
}
