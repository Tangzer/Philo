/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Verdoodt <Verdoodt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:56:56 by tverdood          #+#    #+#             */
/*   Updated: 2023/01/22 19:46:18 by Verdoodt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_sleep(unsigned long long time_to_sleep, t_table *table)
{
	unsigned long long	start;

	start = get_time_now();
	while (42)
	{
		if (get_time_now() - start >= time_to_sleep)
			break ;
		if (table->someone_dead == 1)
			break ;
	}
	return ;
}

static void	start_dining(t_table *table, t_philo *philo)
{
	start_eating(table, philo);
	if (table->someone_dead == 1)
		return ;
	else
		print_log(table, philo, THINK);
	return ;
}

static void	philo_loop(t_table *data)
{
	t_table	*table;
	t_philo	*philo;

	table = data;
	philo = table->philo[table->index];
	table->index++;
	if (philo->id_philo % 2 == 0)
		ft_sleep(10, table);
	while (table->nb_times_each_philo_must_eat == -1
		|| table->nb_rounds < table->nb_times_each_philo_must_eat)
	{
		if (table->someone_dead == 1)
			break ;
		if (table->nb_philo >= 1)
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
		{
			free(table->thread);
			return (print_error("pthread_create() failed."));
		}
		i++;
	}
	return (true);
}
