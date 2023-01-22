/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tverdood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:05:54 by tverdood          #+#    #+#             */
/*   Updated: 2023/01/16 18:05:57 by tverdood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_philo_forks_in_hand(t_table *table, int id)
{
	if (table->nb_philo == 1)
		table->philo[id]->left_fork = &table->forks[0];
	else
	{
		if (id == table->nb_philo - 1)
		{
			table->philo[id]->left_fork = &table->forks[id];
			table->philo[id]->right_fork = &table->forks[0];
		}
		else
		{
			table->philo[id]->left_fork = &table->forks[id];
			table->philo[id]->right_fork = &table->forks[id + 1];
		}
	}
}

bool	init_mutex_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks)
		return (print_error("malloc() failed."));
	memset(table->forks, 0, sizeof(pthread_mutex_t));
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (print_error("pthread_mutex_init() failed."));
		i++;
	}
	return (true);
}
