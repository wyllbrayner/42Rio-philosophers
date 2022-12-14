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

int	ft_isspace(int c)
{
	unsigned char	chr;

	chr = (unsigned char)c;
	if ((chr >= 9 && chr <= 13) || (chr == 32))
		return (TRUE);
	return (FALSE);
}

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

long	ft_atol(char *str)
{
	int		i;
	int		signal;
	long	nbr;

	i = 0;
	signal = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
	nbr = 0;
	while (ft_isdigit(str[i]))
	{
		nbr = (10 * nbr) + (str[i] - '0');
		i++;
	}
	return (signal * nbr);
}

void ft_valid_input_amount(int argc, t_philo *t_ph)
{
    if (argc < 5 || argc > 6)
        t_ph->ret = -1;
}

int	ft_valid_character(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (((str[i] == '-') || (str[i] == '+')) && (!str[i + 1]))
		return (-2);
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-2);
		i++;
	}
	return (0);
}

t_philo	*ft_valid_input_character(char **argv, t_philo *t_ph)
{
	int		i;

	i = 1;
	while (argv[i])
	{
        printf("%s\n", argv[i]);
		if (ft_valid_character(argv[i]) < 0)
		{
			t_ph->ret = -2;
			return (t_ph);
		}
		i++;
	}
	return (t_ph);
}

t_philo *ft_check_input(int argc, char **argv, t_philo *t_ph)
{
    ft_valid_input_amount(argc, t_ph);
    if (t_ph->ret < 0)
        return (t_ph);
    ft_valid_input_character(argv, t_ph);
	if (t_ph->ret < 0)
		return (t_ph);
	return (t_ph);
}

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

t_philo ft_philosophers(int argc, char **argv)
{
    t_philo t_ph;

    t_ph.ret = 0;
    ft_check_input(argc, argv, &t_ph);
    if (t_ph.ret < 0)
        return (t_ph);
    ft_init_struct(argv, &t_ph);
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
/*
*/

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

*/

/*
Passos 
0 - montar o arquivo Makefile.
1 - validar as entradas (pode usar o processo de validacao da push_swap);

2 - montar o processo de validação do programa (quando ele deve encerrar);


*/