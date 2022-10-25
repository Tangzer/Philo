
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdatomic.h>

typedef struct s_philo
{
	struct s_table	*table_;
	int				id;
	int				state;
	atomic_long		last_meal;
	atomic_int		nb_meals;
}	t_philo;

typedef struct s_table
{
	t_philo			*philo;
	pthread_t		*tid;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*prints;
	pthread_mutex_t	*death;
	atomic_int		nb_philo;
	atomic_int		total_meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			start_time;
	atomic_bool		are_full;
	atomic_bool		someone_died;
}	t_table;

/* -Initialize- */
bool	initialize(t_table *table, char **av, int ac);

/* -Mutexes and threads- */
bool		ft_create_mutexes(t_table *table);
//bool		ft_create_threads(t_table *table);

/* -Utils- */
bool	print_error(char *str);
bool	ft_isdigit(char *str);
int		ft_atoi(const char *str);
long	get_time_now(void);

#endif
