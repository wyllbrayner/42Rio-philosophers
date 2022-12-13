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

int main(void)
{
    printf("Entrou na main\n");
    return (0);
}

void ft_philosophers(int argc, char **argv)
{

}

/*
-> Entendimento do programa
--> Um ou mais philosofos sentam ao redor de uma mesa circular.
--> Os philosophos, comem, pensam ou dormem alternadamente.
---> Enquanto eles comem, não pensam nem dormem.  
---> Enquanto eles pensam, não comem nem dormem.  
---> Enquanto eles dormem, não pensam nem comem.
--> Existem tantos garfos quanto philosophos na mesa.
---> exemplo: cada philosopho possui seu proprio garfo a direita.
--> Para comer, cada philosopho precisa pegar o seu próprio garfo e o garfo a sua esquerda.
--> Quando o philosopho termina de comer, coloca os garfos de volta na mesa e começa a dormir.
--> Quando acordado, ele começa a pensar novamente.
---> Comer => Dormir => Pensar
--> A simulação encerra quando o philosofo morre de fome.
--> Cada philosopho precisa comer em nunca morrer de fome.
--> Um philosofo nunca fala com outro.
--> Um philosofo não sabe e um philosopho está prestes a morrer.

-> Regras Gerais
--> Variáveis Globais são proibidas.
--> Entradas: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
number_of_philosophers: Número de Philosophers (e o número de garfos).
time_to_die (miliseconds): O philosopho morre se não começa a comer time_to_die desde o início da última refeição ou do início da simulação.
time_to_eat (miliseconds): O tempo que o philosopho gasta para comer.
time_to_sleep (miliseconds): O tempo que cada philosopher gasta para dormir.
[number_of_times_each_philosopher_must_eat] (opcional): Se cada philosopho comer, pelo menos, esta quantidade de vezes, a simulação pode encerrar. Caso não seja definida, a simulação permanece executando para sempre ou até que algum philosofo morra.
--> Cada Philosopho possui um número de 1 até number_of_philosophers.
--> O philosopho 1 senta na possição seguinte do philosopho N. de tal forma que qualquer philosopho N senta entre os philosophos N + 1 e N - 1. 
--> Qualquer mudança no Philosopho deve ser formatada da seguinte forma:
---> timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
---> timestamp_in_ms X is sleeping
---> timestamp_in_ms X is thinking
---> timestamp_in_ms X died
--> A mensagen de um philosopho não deve se misturar com a mensagem de outro.
--> A mensagem anuncionando a norte de um philosopho deve ser impressa em menos de 10 ms após a morte do mesmo.

-> O programa não deve ter data races.
-> Cada philosopho deve ser uma thread.
--> Não está falando que não pode existirem outras threads alem das necessárias para criar cada philosopho.
--> Para prevenir que um philosopho tenha cargos duplicados, devemos proteger o status de cada garfo com um mutex. 

funcções permitidas:

memset
printf
malloc/free
write
int usleep(microseconds): retorna 0 se tiver sucesso em colocar para dormir e -1 caso não consiga.
int gettimeofday(): retorna 0 se tiver sucesso e -1 caso obtenha erro.
int phtread_create(pthread_t *th, NULL, void *(*start_routine)(void *), void *arg): retorna 0 se conseguir criar uma thread e outro número caso não consiga cria-la.
int pthread_datach(pthread_t th);
pthread_join
pthread_mutex_init
pthread_mutex_destroy
pthread_mutex_lock
pthread_mutex_unlock

*/

/*
Passos 
0 - montar o arquivo Makefile.
    está dando erro ao remover, pois o nome da pasta é o mesmo do programa.

1 - validar as entradas (pode usar o processo de validacao da push_swap);

2 - montar o processo de validação do programa (quando ele deve encerrar);


*/