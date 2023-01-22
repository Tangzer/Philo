/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Verdoodt <Verdoodt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:56:51 by tverdood          #+#    #+#             */
/*   Updated: 2023/01/22 15:42:43 by Verdoodt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	is_valid_args(t_table *table, int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!ft_isdigit(av[i]))
			return (print_error("Invalid arguments."));
		i++;
	}
	if (table->nb_philo < 1 || table->nb_philo > 200)
		return (print_error("Invalid number of philosophers."));
	if (table->time_to_die < 0 || table->time_to_eat < 0
		|| table->time_to_sleep < 0
		|| table->nb_times_each_philo_must_eat < -1)
		return (print_error("Time argument is invalid"));
	if (table->time_to_die > ULONG_MAX || table->time_to_eat > INT_MAX
		|| table->time_to_sleep > INT_MAX
		|| table->nb_times_each_philo_must_eat > INT_MAX)
		return (print_error("Time argument is invalid"));
	if (ac == 6 && table->nb_times_each_philo_must_eat <= 0)
		return (print_error("number of eat is invalid"));
	return (true);
}

static bool	init_args(t_table *table, char **av, int ac)
{
	table->error = 0;
	if (ac < 5 || ac > 6)
		return (print_error("The number of arguments is invalid."));
	memset(table, 0, sizeof(t_table));
	table->nb_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->nb_times_each_philo_must_eat = ft_atoi(av[5]);
	else
		table->nb_times_each_philo_must_eat = -1;
	if (!is_valid_args(table, ac, av))
		return (false);
	table->nb_philo_who_ate_this_round = 0;
	table->nb_rounds = 0;
	table->someone_dead = 0;
	table->index = 0;
	table->dinner_starting_time = get_time_now();
	return (true);
}

static t_philo	*init_philo_data(int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	philo->id_philo = id;
	return (philo);
}

static bool	init_philos(t_table *table)
{
	int	i;

	table->philo = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philo)
		return (print_error("malloc() failed."));
	memset(table->philo, 0, sizeof(t_philo *) * table->nb_philo);
	i = 0;
	while (i < table->nb_philo)
	{
		table->philo[i] = init_philo_data(i + 1);
		if (!table->philo[i])
			return (print_error("malloc() failed."));
		i++;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		init_philo_forks_in_hand(table, i);
		i++;
	}
	return (true);
}

t_table	*protect_and_init(char **av, int ac)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!init_args(table, av, ac))
		table->error = 1;
	else if (!init_mutex_forks(table))
		table->error = 2;
	else if (pthread_mutex_init(&table->print, NULL) != 0)
		table->error = 3;
	else if (!init_philos(table))
		table->error = 4;
	return (table);
}
