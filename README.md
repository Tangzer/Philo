# philosophers

The dining philosophers problem in C, built at École 42 (Brussels).

Each philosopher is a thread; each fork is a mutex. The program must keep every philosopher alive as long as possible, without data races or deadlocks, and report a death within 10 ms.

## Build and run

```bash
cd philo && make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]

# example: 5 philosophers, nobody should die
./philo 5 800 200 200
```

Times are in milliseconds.

## Concepts

POSIX threads, mutexes, race conditions, deadlock avoidance, precise timing with `usleep` and `gettimeofday`.
