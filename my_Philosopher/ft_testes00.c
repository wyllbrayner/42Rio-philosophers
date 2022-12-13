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

#include <stdio.h>
#include <stdlib.h>  // printf e malloc
#include <pthread.h> // thread
#include <unistd.h>  // sleep

// cc ft_testes.c -Wall -Werror -Wextra -pthread -o test && ./test

int x = 2;

void*    ft_routine1()
{
    sleep(1);
    x++;
    printf("Test from thread1 by pid: %d | x: %d\n", getpid(), x);
//    printf("Ending    thread by pid: %d\n", getpid());
//    exit(EXIT_SUCCESS);
    return (0);
}

void*    ft_routine2()
{
//    x++;
    printf("Test from thread2 by pid: %d | x: %d\n", getpid(), x);
    sleep(1);
    printf("Test from thread2 by pid: %d | x: %d\n", getpid(), x);
//    printf("Ending    thread by pid: %d\n", getpid());
//    exit(EXIT_SUCCESS);
    return (0);
}

int main(void)
{
    pthread_t    t1;
    pthread_t    t2;

    if (pthread_create(&t1, NULL, &ft_routine1, NULL) != 0)
        return (-1);
    if (pthread_create(&t2, NULL, &ft_routine2, NULL) != 0)
        return (-2);
    // cria uma nova thread e a associa a variável t1 (do tipo padrão [primeiro NULL]. Essa thread executará a função ft_routine (com retorno void *), que não recebe parâmetros. Logo é passado NULL como último parâmetro. Entretanto, caso a função ft_routine recebesse algum parâmetro, declararíamos neste campo. OBS: Caso a função ft_routine necessite de muitos parâmetros, a faça receber uma struct e envie a struct neste campo.
    // caso a função phtread_create não consiga criar a thread, será retornado um int diferente de zero, que pode ser validado.
    if (pthread_join(t1, NULL) != 0)
        return (-2);
    if (pthread_join(t2, NULL) != 0)
        return (-2);
    // essa função "aguarda" o término da thread associada à variável t1 e impede a conclusão do restante do código da função main. Caso a função ft_routine devolva algum valor, este pode ser capturado pelo ponteiro adicional à função. Como nossa função nada retorna, colocamos NULL neste campo.
    // caso a função pthread_join não consiga aguardar o retorno da thread especificada, será retornado um int diferente de zero, que pode ser validado.

    printf("Após o join       by pid: %d\n", getpid());
    return (0);
}