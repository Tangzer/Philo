# include "../include/philo.h"

void	print_log(t_philo *philo, char *message)
{
	atomic_long	timestamp_in_ms;

	pthread_mutex_lock(&philo->table_->mutex_print);
	if (philo->table_->dinner_in_progress)
	{
		timestamp_in_ms = get_time_now();
		printf("%ld %d %s\n", timestamp_in_ms, philo->id, message);
	}
	pthread_mutex_unlock(&philo->table_->mutex_print);
}

void	philo_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->table_->forks[philo->left_fork]);
	print_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table_->forks[philo->right_fork]);
	print_log(philo, "has taken a fork");
}

void	routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_sleep(philo->table_, 50);
	while (42)
	{

		// why??
		//pthread_mutex_lock(&philo->table_->mutex_print);
		if (philo->table_->dinner_in_progress == 0)
			break;
		//pthread_mutex_unlock(&philo->table_->mutex_print);
		if (philo->table_->nb_philo > 1)
			philo_loop(philo);
	}
	//pthread_mutex_unlock(&philo->table_->mutex_print);
}

int	run_philo_loop(t_table *table)
{
	int i;

	i = 0;
	table->dinner_in_progress = 1;
	table->start_time = get_time_now();
	while (i < table->nb_philo)
	{
		table->philo[i].last_meal = get_time_now();
		if (pthread_create(&table->philo[i].thread, NULL, (void *)routine, &table->philo[i]) != 0)
			return (print_error("pthread_create() failed\n"));
		i++;
	}
	//check dead
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	return (0);
}

/*
bool		ft_create_threads(t_table *table)
{
	int i;

	table->philo = malloc(sizeof(pthread_t) * table->nb_philo);
	if (!table->t_id)
		return (false);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_create(&table->t_id[i], NULL, (void *)routine, &table->philo[i]) != 0)
			return (print_error("pthread_create() failed\n"));
	}
	return (true);
}

static int routine(t_philo *philosopher)
{
	int philo;
	int next;

	philo = philosopher->id;
	next = philo + 1;
	if (philo == philosopher->table_->nb_philo - 1) //cas du dernier philo
		next = 0;
	if ((philosopher->id % 2) == 1) //cas du philo impaire
		ft_sleep(philosopher->table_); //time comme Louise par sécu?
//	if (philosopher->table_->someone_died == 0)
//		eat_and_sleep(philosopher, philo, next);
	return (1);
}*/

int	main(int ac, char **av)
{
	t_table table;

	if (!protect_and_init(&table, av, ac))
		return (EXIT_FAILURE);
	if (!ft_create_mutexes(&table))
		return (EXIT_FAILURE);
	run_philo_loop(&table);
	return (0);
}