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
---> number_of_philosophers: Número de Philosophers (e o número de garfos).
---> time_to_die (miliseconds): O philosopho morre se não começa a comer time_to_die desde o início da última refeição ou do início da simulação.
---> time_to_eat (miliseconds): O tempo que o philosopho gasta para comer.
---> time_to_sleep (miliseconds): O tempo que cada philosopher gasta para dormir.
---> [number_of_times_each_philosopher_must_eat] (opcional): Se cada philosopho comer, pelo menos, esta quantidade de vezes, a simulação pode encerrar. Caso não seja definida, a simulação permanece executando para sempre ou até que algum philosofo morra.
--> Cada Philosopho possui um número de 1 até number_of_philosophers.
--> O philosopho 1 senta na possição seguinte do philosopho N. de tal forma que qualquer philosopho N senta entre os philosophos N + 1 e N - 1. 
--> Qualquer mudança no Philosopho deve ser formatada da seguinte forma:
---> timestamp_in_ms X has taken a fork
---> timestamp_in_ms X is eating
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

OBS: o contador para a morte do philosopher reinicia a cada vez que ele começa a comer.

Passos
0 - (OK) Montar o arquivo Makefile.
1 - (OK) Validar as entradas (pode usar o processo de validacao da push_swap);
    -> se alguma das entradas for inválida:
        => retornar uma mensagem de erro; e
        => encerrar o programa.
    -> se passar pela validação, seguir com o programa.
2 - (XX) Iniciar as variáveis necessárias em uma estrutura;
    -> se a inicialização falhar (ainda estou inicializando apenas com as entradas dos usuários\
    ainda não há error a ser validado):
        => retornar mensagem de error; e
        => encerrar o programa.
    -> se passar pela inicialização, seguir com o programa. 
3 - (XX) Inicializar a quantidade de philosophers (threades) de acordo com o input recebido.
    -> se a inicialização de algum dos philosophos falhar:
        => encerrar as threads já inicializadas;
        => liberar a memória (caso tenha sido alocada);
        => escrever mensagem de error; e
        => encerrar o programa.
    -> se passar pela inicialização, seguir com o programa.
4 - (XX) Inicializar uma thread adicional para monitorar as condições de parada do programa (alguma \
    thread morrer (ou todos os philosophos conseguirem comer, pelo menos, a quatidade estipulada [se definido]));
    -> se alguma condição de parada for alcançada:
        => escrever na tela que o philosopher morreu;
        => encerrar as threads já inicializada;
        => liberar a memória já alocada (se aplicado); e
        => encerrar o programa.
    -> enquanto a condição de parada não for alcançada, seguir com o programa.
5 - (XX) Cada philosopho deve executar uma mesma rotina.
    -> Esta rotina deve ficar em loop infinito até que a condição de parada seja alcançada.
    --> a rotina deve chamar as seguintes atividades:
        ---> comer;
        ----> Essa atividade deve chamar uma função comer que fará as seguintes atividades:
        -----> capturar o mutex para o garfo direito;
        -----> imprimir "timestamp_in_ms X has taken a fork";
        -----> capturar o mutex para o garfo esquerdo;
        -----> imprimir "timestamp_in_ms X has taken a fork";
        -----> capturar o mutex para impressão;
        -----> calcular o timestamp_in_ms para impressão final.
        -----> imprimir "timestamp_in_ms X is eating";
        -----> devolver o mutex para impressão;
        -----> devolver o mutex para o garfo direito;
        -----> devolver o mutex para o garfo esquerdo;
        ---> dormir;
        ---> Essa atividade deve chamar uma função dormir que fará as seguintes atividades:
        ----> capturar o mutex para impressão;
        ----> calcular o timestamp_in_ms para impressão final.
        ----> imprimir "timestamp_in_ms X is sleeping";
        ----> devolver o mutex para impressão;
        ---> pensar;
        ---> Essa atividade deve chamar uma função pensar que fará as seguintes atividades:
        ----> capturar o mutex para impressão;
        ----> calcular o timestamp_in_ms para impressão final.
        ----> imprimir "timestamp_in_ms X is thinking";
        ----> devolver o mutex para impressão;
6 - (XX) A thread monitor deve executar uma rotina que verifica se todos os philosophos estão vivos e \
    se todos já comeram a quantidade determinada (se aplicado).
    -> essa rotina devem conter um loop infinito validando as condições de parada.
    --> condições de parada:
    ---> Algum philósopho morrer; e 
    ---> Todos os philosophos commerar a quantidade estipulada (se aplicado).
    -> Uma vez fora do loop infinito, este monitor deve chamar a função que encerra as demais threads \
    e encerrar o programa.

Conversão entre:
1 segundo = 1.000 milissegundos        (ou 1/1000 segundo = 1 milissegundo).
1 microssegundo = 1/1000 milissegundos (ou 1000 microssegundos = 1 milissegundo).
segundo > milissegundo > microssegundo

o usleep recebe microssegundos, mas trabalhamos com milissegundos. Logo, \
precisaremos multiplicar os milissegundos por 1000 para enviar a quantidade certa de microssegundos \
ao usleep.

o gettimeofday devolve a quantidade de segundos e de microssegundos decorridos deste meados de 1970. A devolutiva \
desta função ocorre mediante uma struct contendo dois campos. Um campo contendo a quantidade de segundos decorridos \
desde o início da contagem até a sua chamada pelo programa e o segundo campo contendo a quantidade de microssegundos \
decorridos.
Neste projeto precisamos converter ambos os campos para milessegundos ((segundos + 1000) + (microssegundos / 1000)).

*/