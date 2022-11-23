#include "../include/philo.h"

static bool	someone_is_starving(t_table *table, t_philo *philo)
{
	unsigned long	time_without_eating;

	time_without_eating = get_time_now() - philo->last_meal;
	if (time_without_eating >= table->time_to_die)
	{
		pthread_mutex_lock(&table->print);
		table->someone_dead = 1;
		pthread_mutex_unlock(&table->print);
		print_log(table, philo, DEAD);
		return (true);
	}
	return (false);
}

static bool	bellies_are_full(t_table *table)
{
	if (table->nb_times_each_philo_must_eat != -1
		&& (table->nb_rounds == table->nb_times_each_philo_must_eat))
	{
		pthread_mutex_lock(&table->print);
		table->someone_dead = 1;
		pthread_mutex_unlock(&table->print);
		return (true);
	}
	return (false);
}

void	check_if_someone_died(t_table *table)
{
	int	i;

	while (42)
	{
		pthread_mutex_lock(&table->print);
		printf("loop\n");
		pthread_mutex_unlock(&table->print);
		i = 0;
		usleep(100);
		while (i < table->nb_philo)
		{
			if (table->someone_dead == 0 && someone_is_starving(table, table->philo[i]))
				return ;
			i++;
		}
		if (bellies_are_full(table))
			return ;
		if (table->someone_dead == 1)
			return ;
		pthread_mutex_lock(&table->print);
		printf("end loop\n");
		pthread_mutex_unlock(&table->print);
	}
}

//// EFFACER les 3 debug au-dessus