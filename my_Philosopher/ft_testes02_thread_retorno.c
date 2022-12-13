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

#define MAX 10

// cc ft_testes.c -Wall -Werror -Wextra -pthread -o test && ./test

pthread_mutex_t mutex;

void*    ft_roll_dice()
{
    pthread_mutex_lock(&mutex); // efetivamente, bloqueia o trecho de código crítico para as threads
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int));
    *result = value;
    printf("%d\n", value); 
    pthread_mutex_unlock(&mutex); // efetivamente, desbloqueia o trecho de código crítico para as threads
    return ((void *)result);
}

// race conditional: corrida de dados/condições ocorre quando duas threads leem e escrevem sobre a mesma variável antes que a outra termine seu processo de escrita e gravação. Gerando resultados inesperados.
int main(void)
{
    int             *res;
    pthread_t       th[MAX];
    int             i = 0;
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL); // inicia um mutex para a parte crítica do código para as threads.
    while (i < MAX)
    {
        printf("Initialize thread %i\n", i);
        if (pthread_create(&th[i], NULL, &ft_roll_dice, NULL) != 0)
            return (-1);
        i++;
    }
    // cria uma nova thread e a associa a variável t1 (do tipo padrão [primeiro NULL]. Essa thread executará a função ft_routine (com retorno void *), que não recebe parâmetros. Logo é passado NULL como último parâmetro. Entretanto, caso a função ft_routine receba algum parâmetro, declararemos neste campo. OBS: Caso a função ft_routine necessite de muitos parâmetros, a faça receber uma struct e envie a struct neste campo.
    // caso a função phtread_create não consiga criar a thread, será retornado um int diferente de zero, que pode ser validado.
    i = 0;
    while (i < MAX)
    {
        if ((pthread_join(th[i], (void **)&res)) != 0) // utilizando a variável res para capturar o retorno da thread e a utilizando na estrutura principal. Foi necessário receber uma variável mallocada, pois, não sendo assim, acessaríamos uma variável que já fora destruida na pilha de execução do programa.
            return (-2);
        printf("To ending thread %i | res: %d\n", i, *res);
        free(res);
        i++;

    }
    // essa função "aguarda" o término da thread associada à variável t1 e impede a conclusão do restante do código da função main. Caso a função ft_routine devolva algum valor, este pode ser capturado pelo ponteiro adicional à função. Como nossa função nada retorna, colocamos NULL neste campo.
    // caso a função pthread_join não consiga aguardar o retorno da thread especificada, será retornado um int diferente de zero, que pode ser validado.

    pthread_mutex_destroy(&mutex); //encerra o mutex, encerra a parte crítica do código para as threads

    printf("Após o join by pid: %d\n", getpid());
    return (0);
}