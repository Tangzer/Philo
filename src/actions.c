# include "../include/philo.h"

static void	take_right_fork(t_table *table, t_philo *philo)
{
	if (table->someone_dead == 1)
		return ;
	pthread_mutex_lock(philo->right_fork);
	print_log(table, philo, FORK);
}

static void	take_left_fork(t_table *table, t_philo *philo)
{
	if (table->someone_dead == 1)
		return ;
	pthread_mutex_lock(philo->left_fork);
	print_log(table, philo, FORK);
	if (table->nb_philo == 1)
		ft_sleep(table->time_to_die + 10, table);
}

static void	sleeping(t_table *table, t_philo *philo)
{
	print_log(table, philo, SLEEP);
	ft_sleep(table->time_to_sleep, table);
}

static void	eating(t_table *table, t_philo *philo)
{
	print_log(table, philo, EAT);
	if (table->nb_times_each_philo_must_eat != -1
			&& table->nb_philo_who_ate_this_round < table->nb_philo)
	{
		table->nb_philo_who_ate_this_round++;
		if (table->nb_philo_who_ate_this_round == table->nb_philo)
		{
			table->nb_philo_who_ate_this_round = 0;
			table->nb_rounds++;
		}
		ft_sleep(table->time_to_sleep, table);
	}
}

void		start_eating(t_table *table, t_philo *philo)
{
	if (table->nb_philo == 1)
		take_left_fork(table, philo);
	else
	{
		take_left_fork(table, philo);
		take_right_fork(table, philo);
		eating(table, philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		sleeping(table, philo);
	}
}
