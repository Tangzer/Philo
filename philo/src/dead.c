/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tverdood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:56:42 by tverdood          #+#    #+#             */
/*   Updated: 2023/01/16 17:57:12 by tverdood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	dead(t_table *table, t_philo *philo)
{
	if (get_time_now() >= (philo->last_meal + table->time_to_die))
	{
		print_log(table, philo, DEAD);
		table->someone_dead = 1;
		return (1);
	}
	return (0);
}

void	check_if_someone_died(t_table *table)
{
	int	i;

	while (table->someone_dead == 0)
	{
		i = 0;
		while (table->someone_dead == 0 && i < table->nb_philo)
		{
			if (dead(table, table->philo[i]))
				return ;
			i++;
		}
	}
	return ;
}
