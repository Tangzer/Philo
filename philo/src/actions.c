/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Verdoodt <Verdoodt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:56:40 by tverdood          #+#    #+#             */
/*   Updated: 2023/01/22 19:50:35 by Verdoodt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
}

static void	sleeping(t_table *table, t_philo *philo)
{
	print_log(table, philo, SLEEP);
	ft_sleep(table->time_to_sleep, table);
}

static void	eating(t_table *table, t_philo *philo)
{
	print_log(table, philo, EAT);
	philo->last_meal = get_time_now();
	ft_sleep(table->time_to_eat, table);
	philo->last_meal = get_time_now();
	if (table->nb_times_each_philo_must_eat != -1
		&& table->nb_philo_who_ate_this_round < table->nb_philo)
	{
		table->nb_philo_who_ate_this_round++;
		if (table->nb_philo_who_ate_this_round == table->nb_philo)
		{
			table->nb_philo_who_ate_this_round = 0;
			table->nb_rounds++;
			if (table->nb_rounds == table->nb_times_each_philo_must_eat)
				table->someone_dead = 1;
		}
	}
}

void	start_eating(t_table *table, t_philo *philo)
{
	if (table->nb_philo == 1)
	{
		take_left_fork(table, philo);
		ft_sleep(table->time_to_die + 100, table);
	}
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
