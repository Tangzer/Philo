# include "../include/philo.h"

static int	parsing(int ac, char **av)
{
	int i;

	if (ac < 5 || ac > 6)
		return (print_error("Wrong number of arguments."));
	i = 0;
	while (i < ac)
	{
		if (!ft_isdigit(av[i]))
			return (print_error("Please only enter digits."));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table table;

	if (parsing(ac, av))
		return (EXIT_FAILURE);
	if (!initialize(&table, av, ac))
		return (EXIT_FAILURE);
	if (!ft_create_mutexes(&table))
		return (EXIT_FAILURE);
	return (0);
}