/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tverdood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:05:50 by tverdood          #+#    #+#             */
/*   Updated: 2023/01/16 18:06:01 by tverdood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_log(t_table *table, t_philo *philo, int status)
{
	unsigned long long	time;

	pthread_mutex_lock(&table->print);
	time = get_time_now() - table->dinner_starting_time;
	if (status == FORK && table->someone_dead == 0)
		printf("%lld %d has taken a fork\n", time, philo->id_philo);
	else if (status == EAT && table->someone_dead == 0)
		printf("%lld %d is eating\n", time, philo->id_philo);
	else if (status == SLEEP && table->someone_dead == 0)
		printf("%lld %d is sleeping\n", time, philo->id_philo);
	else if (status == THINK && table->someone_dead == 0)
		printf("%lld %d is thinking\n", time, philo->id_philo);
	else if (status == DEAD)
		printf("%lld %d died\n", time, philo->id_philo);
	pthread_mutex_unlock(&table->print);
}
