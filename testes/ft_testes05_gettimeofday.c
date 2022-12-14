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

#include <stdio.h>   // printf
#include <stdlib.h>  // malloc
#include <pthread.h> // thread
#include <unistd.h>  // sleep
#include <time.h>    // função time 
#include <sys/time.h>// timeval

#define MAX 2

// cc ft_testes.c -Wall -Werror -Wextra -pthread -o test && ./test
/*
struct    timeval  {
  time_t        tv_sec ;   //used for seconds
  suseconds_t       tv_usec ;   //used for microseconds
}
*/
int main(void)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    usleep(1000);
    gettimeofday(&end, NULL);
    printf("end         : %ld\n", end.tv_usec);
    printf("start       : %ld\n", start.tv_usec);
    printf("elapsed time: %ld\n", end.tv_usec - start.tv_usec);
    return (0);
}