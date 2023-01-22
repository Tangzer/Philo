/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Verdoodt <Verdoodt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:56:54 by tverdood          #+#    #+#             */
/*   Updated: 2023/01/22 16:30:40 by Verdoodt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned long long	get_time_now(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

bool	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_join(table->thread[i], NULL) != 0)
		{
			free(table->thread);
			return (print_error("pthread_join() failed."));
		}
		i++;
	}
	free(table->thread);
	return (true);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = protect_and_init(av, ac);
	if (table->error == 1 || table->error == 2 || table->error == 3
		|| table->error == 4)
		return (free_and_exit(table, table->error));
	if (!run_philo_loop(table))
		return (free_and_exit(table, 4));
	check_if_someone_died(table);
	if (!join_threads(table))
		return (free_and_exit(table, 4));
	if (!destroy_print_mutex(table))
		return (free_and_exit(table, 4));
	if (!destroy_fork_mutexes(table))
		return (free_and_exit(table, 4));
	free_philos(table);
	free(table);
//	system("leaks philo");
	return (0);
}
