# philosophers
O philosophers é baseado no problema de sincronização da ciência da computação "O Jantar dos Filósofos" ([The Dining Philosopher Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)).
O philosophers consiste em uma analogia de filósofos sentados ao redor de uma mesa redonda de jantar e existe um grande prato de espaguete no meio dessa mesa. Cada filósofo precisa de dois garfos para comer e na mesa existe um garfo por filósofo. Os filósofos podem alternar entre comer, pensar e dormir, e cada filósofo não executa duas ações ao mesmo tempo. O problema em questão é implementar um algoritmo em que os filósofos executem essas ações sem ficarem travados, utilizando *threads* e *mutexes*.

### Como compilar?
Utilizando o Makefile você pode criar o arquivo executável *philo*
```
make
```

### Como executar?
Rode o executável *philo*, passando como argumentos:
| 1 | 2 | 3 | 4 | 5 |
|----------|:-------------:|:-------------:|:-------------:|:-------------:|
| number_of_philosophers | time_to_die | time_to_eat | time_to_sleep | number_of_times_each_philosopher_must_eat |
* number_of_philosophers: É a quantidade de filósofos e de garfos;
* time_to_die (in milliseconds): Se um filósofo não começar a comer *time_to_die* milissegundos desde o início de sua última refeição ou o início da simulação, ele morre;
* time_to_eat (in milliseconds): O tempo que leva para um filósofo comer. Durante esse tempo, ele precisa segurar dois garfos;
* time_to_sleep (in milliseconds): O tempo que um filósofo passará dormindo;
* number_of_times_each_philosopher_must_eat (argumento opcional): Se todos os filósofos comerem pelo menos *number_of_times_each_philosopher_must_eat* vezes a simulação para. Se não for especificado, a simulação para quando um filósofo morre.

Exemplos:
```
./philo 4 300 100 100
```
ou
```
./philo 4 300 100 100 7
```


#### More about School 42 you can find here: https://en.wikipedia.org/wiki/42_(school)
