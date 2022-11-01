# include "../include/philo.h"


void	ft_sleep(t_table *table, int time)
{
	while (table->dinner_in_progress == 1 && time > 50)
		usleep(100);
	return;
}

/*
void	eat_and_sleep(t_philo *philo, int phi_id, int next)
{
	while (philo->table_->someone_died == 0 && philo->table_->is_full == 0)
	{
		//boucle infinie dans le cas ou il n'y a qu'un philo
		pthread_mutex_lock(&philo->table_->fork[phi_id]);
		pthread_mutex_lock(&philo->table_->fork[next]);
		print_with_mutex(philo, philo->table_->thread_to_print_msg, "has taken a fork");
		mutex_for_prints(philo, philo->table->prints, "is eating\n");

	}
}
*/
