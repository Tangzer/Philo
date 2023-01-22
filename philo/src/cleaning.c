/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Verdoodt <Verdoodt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:56:54 by tverdood          #+#    #+#             */
/*   Updated: 2023/01/22 15:52:32 by Verdoodt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	free_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo && table->philo[i])
	{
		free(table->philo[i]);
		i++;
	}
	free(table->philo);
	return (true);
}

bool	destroy_fork_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_unlock(&table->forks[i]) != 0)
			return (print_error("pthread_mutex_unlock() failed."));
		if (pthread_mutex_destroy(&table->forks[i]) != 0)
			return (print_error("pthread_mutex_destroy() failed."));
		i++;
	}
	free(table->forks);
	return (true);
}

bool	destroy_print_mutex(t_table *table)
{
	if (pthread_mutex_unlock(&table->print) != 0)
		return (print_error("pthread_mutex_unlock() failed."));
	if (pthread_mutex_destroy(&table->print) != 0)
		return (print_error("pthread_mutex_destroy() failed."));
	return (true);
}

int	free_and_exit(t_table *table, int k)
{
	if (k == 4)
		free_philos(table);
	if (k == 3 || k == 4)
		destroy_print_mutex(table);
	if (k == 2 || k == 3 || k == 4)
		destroy_fork_mutexes(table);
	if (k == 1 || k == 2 || k == 3 || k == 4)
		free(table);
	return (EXIT_FAILURE);
}
