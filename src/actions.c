# include "../include/philo.h"

static void	check_if_someone_is_starving(t_table *table, t_philo *philo)
{
	unsigned long	time_without_eating;
	unsigned long	time_died;

	time_without_eating = get_time_now() - philo->last_meal;
	if (table->time_to_die < time_without_eating)
	{
		pthread_mutex_lock(&table->mutex_print);
		time_died = get_time_now() - table->start_time;
		printf("[%ld] - %d %s\n", time_died, philo->id, "died");
		table->dinner_in_progress = 0;
		pthread_mutex_unlock(&table->mutex_print);
	}
}

static void	check_if_bellies_are_full(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (table->philo[i].meals_count < table->nb_of_times_each_philo_must_eat)
			return ;
		i++;
	}
	pthread_mutex_lock(&table->mutex_print);
	table->dinner_in_progress = 0;
	pthread_mutex_unlock(&table->mutex_print);
}

void	check_if_someone_died(t_table *table)
{
	int i;

	while (table->dinner_in_progress)
	{
		i = 0;
		usleep(100);
		while (table->dinner_in_progress && i < table->nb_philo)
		{
			pthread_mutex_lock(&table->death);
			check_if_someone_is_starving(table, &table->philo[i]);
			pthread_mutex_unlock(&table->death);
			i++;
		}
		if (table->nb_of_times_each_philo_must_eat > 0)
		{
			pthread_mutex_lock(&table->death);
			check_if_bellies_are_full(table);
			pthread_mutex_unlock(&table->death);
		}
	}
}

void	ft_action(t_table *table, int time)
{
	unsigned long	start;
	unsigned long	duration;

	start = get_time_now();
	duration = (unsigned long)time;
	while (42)
	{
		if (get_time_now() - start >= duration)
			break ;
		pthread_mutex_lock(&table->mutex_print);
		if (table->dinner_in_progress == 0)
		{
			pthread_mutex_unlock(&table->mutex_print);
			break ;
		}
		pthread_mutex_unlock(&table->mutex_print);
		usleep(100);
	}
}
