# include "../include/philo.h"

//proteger les arguments au dessus du int max ?
static bool	is_valid_args(t_table *table, int ac, char **av)
{
	int i;

	if (ac < 5 || ac > 6)
		return (print_error("The number of arguments is invalid."));
	i = 1;
	while (i < ac)
	{
		if (!ft_isdigit(av[i]))
			return (print_error("Invalid arguments."));
		i++;
	}
	if (table->nb_philo < 1 || table->nb_philo > 200)
		return (print_error("Invalid number of philosophers."));
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		return (print_error("Time argument is invalid"));
/// ?? argc == 6 &&
	if (table->total_meals <= 0)
		return (print_error("number of eat is invalid"));
	return (false);
}

static bool	init_each_philo(t_table *table)
{
	int i;

	table->philo = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philo)
		return (false);
	i = 0;
	while (i < table->nb_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = (i + 1) % table->nb_philo;
		table->philo[i].nb_meals = 0;
		table->philo[i].table_ = table;
		i++;
	}
	return (true);
}

bool	init_args(t_table *table, char **av, int ac)
{
	memset(table, 0, sizeof(t_table));
	table->nb_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->total_meals = ft_atoi(av[5]);
	else
		table->total_meals = 0;
	return (true);
}

bool	protect_and_init(t_table *table, char **av, int ac)
{
	if (!is_valid_args(table, ac, av))
		return (false);
	if (!init_args(table, av, ac))
		return (false);
	if (!init_each_philo(table))
		return (false);
	return (true);
}