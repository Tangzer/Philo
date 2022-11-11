# include "../include/philo.h"

static void	start_dining(t_table *table, t_philo *philo)
{
	start_eating(table, philo);
	if (table->someone_dead == 1)
		return ;
	else
		print_log(table, philo, THINK);
	return ;
}

static void	philo_loop(t_table *table)
{
	t_philo	*philo;

	philo = &table->philo[table->index];
	table->index++;
	if (philo->id_philo % 2 == 0) {
		ft_sleep(100);
	}
	while (table->nb_times_each_philo_must_eat == -1
			|| table->nb_rounds < table->nb_times_each_philo_must_eat)
	{
		if (!table->someone_dead) {
			start_dining(table, philo);
		}
		else {
			break ;
		}
	}
}

bool	run_philo_loop(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nb_philo)
	{
		init_philo_forks_in_hand(table, i);
		table->philo[i].last_meal = get_time_now();
		if (pthread_create(&table->philo[i].thread, NULL, (void *)philo_loop, table) != 0)
			return (print_error("pthread_create() failed."));
		i++;
	}
	check_if_someone_died(table);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			return (print_error("pthread_join() failed."));
		i++;
	}
	return (true);
}
