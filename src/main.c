#include "../include/philo.h"

unsigned long long	get_time_now(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(unsigned long long time_to_sleep, t_table *table)
{
	unsigned long long	start;

	start = get_time_now();
	while (42)
	{
		if (get_time_now() - start >= time_to_sleep)
			break ;
		pthread_mutex_lock(&table->print);
		if (table->someone_dead)
		{
			pthread_mutex_unlock(&table->print);
			break ;
		}
		pthread_mutex_unlock(&table->print);
		usleep(100);
	}
	return ;
}

void	print_log(t_table *table, t_philo *philo, int status)
{
	unsigned long long	time;

	pthread_mutex_lock(&table->print);
	time = get_time_now() - table->dinner_starting_time;
	if (status == FORK && table->someone_dead == 0)
		printf("%lld %d has taken a fork\n", time, philo->id_philo);
	else if (status == EAT && table->someone_dead == 0)
		printf("%lld %d is eating\n", time, philo->id_philo);
	else if (status == SLEEP && table->someone_dead == 0)
		printf("%lld %d is sleeping\n", time, philo->id_philo);
	else if (status == THINK && table->someone_dead == 0)
		printf("%lld %d is thinking\n", time, philo->id_philo);
	else if (status == DEAD)
		printf("%lld %d died\n", time, philo->id_philo);
	pthread_mutex_unlock(&table->print);
}


static bool	clear_the_table(t_table *table)
{
	int	i;

	i = 0;

	while (i < table->nb_philo)
	{
		free(table->philo[i]);
		i++;
	}
	free(table->philo);
	free(table->forks);
	free(table->thread);
	return (true);
}

bool	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		int err = 0;
		err = pthread_detach(table->thread[i]);
		if (err != 0)
		{
			printf("err = %d\n", err);
			return (print_error("pthread_detach() failed+."));
		} //EFFACER
		pthread_mutex_unlock(&table->forks[i]);
		err = pthread_mutex_destroy(&table->forks[i]);
		if (err != 0)
		{
			printf("err = %d\n", err);
			return (print_error("pthread_mutex_destroy() failed-."));
		} //effacer
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = protect_and_init(av, ac);
	if (!table)
		return (EXIT_FAILURE);
	if (!run_philo_loop(table))
		return (EXIT_FAILURE);
	printf("LOOP OK\n");
	check_if_someone_died(table);
	printf("DEAD LOOP OK\n");
	pthread_mutex_destroy(&table->print);
	printf("MUTEX PRINT OK\n");
	if (!join_threads(table))
		return (EXIT_FAILURE);
	printf("JOIN THREADS OK\n");
	clear_the_table(table);
	printf("table cleared OK\n");
	return (0);
}


// CHECK LEAKS && FREE
// check_if someone_died tourne a l'infini parfois...
// ptrhead_join problematqiue avec bcp de philo