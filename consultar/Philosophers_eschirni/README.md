# philosophers
### I never thought philosophy would be so deadly
<img width="225" src="https://github.com/eschirni/philosophers/blob/master/readme_src/100.png"><img width="600" height="233.5" src="https://github.com/eschirni/philosophers/blob/master/readme_src/philosophers.png">

## Description of the subject
Philosophers is a project about solving the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) by writing a simulation of philosophers sitting around a table. The philosophers alternatively eat, think, or sleep. Once a philosophers is done eating he will sleep, afterwards think and then eat again. There is a fork for every philosopher and 2 forks are needed for a philosopher to eat. Once a philosopher starts eating his time to die will be reset and the other philosophers can't access the forks anymore while he eats. If a philosopher dies the simulation will stop.

This project is about writing effective code, learning about [threads](https://www.geeksforgeeks.org/multithreading-c-2/), [mutexes](https://www.delftstack.com/howto/c/mutex-in-c/) and all the problems that may come along with it, like [data races](https://en.wikipedia.org/wiki/Race_condition).

#### For more details: [subject.pdf](https://github.com/eschirni/philosophers/blob/master/readme_src/philosophers.pdf)

## Installation and execution
1. git clone or fork the repository
2. run `make` to create the executeable
3. run it with `./philo` and the needed arguments (amount of philos, time to die, time to eat, time to sleep, \*number of meals)

\*number of meals is not necessary for the simulation to work

## Sources and tips for 42 students
- I really recommend watching the threads videos by [CodeVault](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2) to get started with threads
- Even though I didn't use one, I recommend using a \*"reaper thread" because it makes your simulation way faster
- Mutex lock everytime you access a shared variable to avoid data races, bools don't need to be locked necessarily because they only have 2 values

\*a reaper thread is a thread running along with the philosophers checking if one of them died and if so exiting the program
