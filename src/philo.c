#include "../include/philo.h"

static void	start_dining(t_table *table, t_philo *philo)
{
	start_eating(table, philo);
	if (table->someone_dead == 1)
		return ;
	print_log(table, philo, THINK);
	return ;
}

static void	philo_loop(t_table *data)
{
	t_table	*table;
	t_philo	*philo;

	table = (t_table *)data;
	philo = table->philo[table->index];
	table->index++;
	if (philo->id_philo % 2 == 0)
		ft_sleep(50, table);
	while (table->nb_times_each_philo_must_eat == -1
		|| table->nb_rounds < table->nb_times_each_philo_must_eat)
	{
		pthread_mutex_lock(&table->print);
		if (table->someone_dead == 1)
			break ;
		pthread_mutex_unlock(&table->print);
		if (table->nb_philo > 1)
			start_dining(table, philo);
		else
			break ;
	}
}

bool	run_philo_loop(t_table *table)
{
	int	i;

	table->thread = malloc(sizeof(pthread_t) * table->nb_philo);
	if (!table->thread)
		return (print_error("malloc() failed."));
	i = 0;
	while (i < table->nb_philo)
	{
		table->philo[i]->last_meal = get_time_now();
		if (pthread_create(&table->thread[i], NULL, (void *)philo_loop,
				table) != 0)
			return (print_error("pthread_create() failed."));
		i++;
	}
	return (true);
}
