# include "../include/philo.h"

bool		ft_create_mutexes(t_table *table)
{
	table->fork = malloc(sizeof(pthread_mutex_t) * table->nb_philo);

	return (true);
}

/*
bool		ft_create_threads(t_table *table)
{
	int i;

	i = 0;

	return (true);
}
*/