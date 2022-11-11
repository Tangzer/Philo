# include "../include/philo.h"

static bool	check_if_someone_is_starving(t_table *table, t_philo *philo)
{
	unsigned long	time_without_eating;

	time_without_eating = get_time_now() - philo->last_meal;
	if (table->time_to_die < time_without_eating)
	{
		pthread_mutex_lock(&table->print);
		table->dinner_in_progress = 0;
		pthread_mutex_unlock(&table->print);
		return (true);
	}
	return (false);
}

void	check_if_someone_died(t_table *table)
{
	int	i;

	while (table->dinner_in_progress)
	{
		i = 0;
		usleep(100); //fonctionne bien sans?
		while (table->dinner_in_progress && i < table->nb_philo)
		{
			if (check_if_someone_is_starving(table, &table->philo[i]))
				return ;
			i++;
		}
		if (table->nb_rounds == table->nb_times_each_philo_must_eat)
		{
			pthread_mutex_lock(&table->print);
			return ;
		}
	}
}
