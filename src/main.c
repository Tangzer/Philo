# include "../include/philo.h"

unsigned long	get_time_now(void)
{
	unsigned long	res;
	struct timeval	time;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}

void	print_log(t_philo *philo, char *message)
{
	atomic_long	now;

	now = get_time_now() - philo->table_->start_time;
	pthread_mutex_lock(&philo->table_->mutex_print);
	if (philo->table_->dinner_in_progress)
	{
		printf("[%ld] - %d %s\n", now, philo->id, message);
	}
	pthread_mutex_unlock(&philo->table_->mutex_print);
}

void	clear_the_table(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->mutex_print);
	pthread_mutex_destroy(&table->death);
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(table->forks + i);
		i++;
	}
	free(table->philo);
	free(table->forks);
}

int	main(int ac, char **av)
{
	t_table table;

	if (!protect_and_init(&table, av, ac))
		return (EXIT_FAILURE);
	if (!ft_create_mutexes(&table))
		return (EXIT_FAILURE);
	run_philo_loop(&table);
	clear_the_table(&table);
	return (0);
}

// proteger les arguments au dessus du int max
//-fsanitize=thread
//-fsanitize=address --> malloc
// PROTEGER fct de la lib
// check github Dorian