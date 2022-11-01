# include "../include/philo.h"

bool		ft_create_mutexes(t_table *table)
{
	int i;

	if (pthread_mutex_init(&table->mutex_print, NULL) != 0)
		return (false);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks)
		return (false);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (print_error("pthread_mutex_init() failed\n"));
		i++;
	}
	if (pthread_mutex_init(&table->death, NULL) != 0)
		return (0);
	//death --> ??
	return (true);
}
