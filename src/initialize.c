# include "../include/philo.h"

//proteger les argumetns au dessus du int max ?
static bool	ft_error(t_table *table)
{
	if (table->nb_philo == 0 || table->nb_philo > 2000)
		return (print_error("Incorrect number of philosophers."));
	if ((table->nb_philo <= 0) || (table->time_to_die < 0)
		|| (table->time_to_eat < 0) || (table->time_to_sleep < 0))
		return (print_error("Incorrect arguments."));
	return (false);
}

static bool	init_philo(t_table *table)
{
	int i;

	i = 0;
	table->philo = malloc(sizeof (t_philo) * table->nb_philo);
	if (!table->philo)
		return (false);
	while (i < table->nb_philo)
	{
		table->philo[i].id = i;
		table->philo[i].last_meal = get_time_now();
		table->philo[i].nb_meals = 0;
		table->philo[i].table_ = table;
		i++;
	}
	return (true);
}

bool	initialize(t_table *table, char **av, int ac)
{
	memset(table, 0, sizeof(t_table));
	table->nb_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->total_meals = ft_atoi(av[5]);
	else
		table->total_meals = -1;
	if (ft_error(table))
		return (false);
	if (!init_philo(table))
		return (false);
	table->start_time = get_time_now();
	return (true);
}