/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/07/09 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOSOPHER_H
# define FT_PHILOSOPHER_H

# include <stdio.h>   // printf
# include <stdlib.h>  // malloc e free
# include <unistd.h>  // sleep

# include <pthread.h> // thread

# define FALSE	0
# define TRUE	1

typedef struct      philo
{
    int             ret;
    long            nbr_philo;
    long            nbr_fork;
    suseconds_t     t_to_die;
    suseconds_t     t_to_eat;
    suseconds_t     t_to_sleep;
    long            t_must_eat;
}                   t_philo;

#endif
