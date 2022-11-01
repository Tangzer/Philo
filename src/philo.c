# include "../include/philo.h"

static void	routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table_->forks[philo->left_fork]);
	print_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table_->forks[philo->right_fork]);
	print_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table_->death);
	print_log(philo, "is eating");
	philo->last_meal = get_time_now();
	philo->meals_count++;
	pthread_mutex_unlock(&philo->table_->death);
	ft_action(philo->table_, philo->table_->time_to_eat);
	pthread_mutex_unlock(&philo->table_->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table_->forks[philo->right_fork]);
	print_log(philo, "is sleeping");
	ft_action(philo->table_, philo->table_->time_to_sleep);
	print_log(philo, "is thinking");
}

static void	philo_loop(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_action(philo->table_, 50);
	while (42)
	{
		pthread_mutex_lock(&philo->table_->mutex_print);
		if (philo->table_->dinner_in_progress == 0)
			break;
		pthread_mutex_unlock(&philo->table_->mutex_print);
		if (philo->table_->nb_philo > 1)
			routine(philo);
	}
	pthread_mutex_unlock(&philo->table_->mutex_print);
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
		if (pthread_create(&table->philo[i].thread, NULL, (void *)philo_loop, &table->philo[i]) != 0)
			return (print_error("pthread_create() failed\n"));
		i++;
	}
	check_if_someone_died(table);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	return (0);
}
