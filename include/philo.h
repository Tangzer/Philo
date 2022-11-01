
#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <stdatomic.h>
# include <stdbool.h>

struct	s_table;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					left_fork;
	int					right_fork;
	atomic_long			last_meal;
	atomic_int			meals_count;
	struct s_table		*table_;
}	t_philo;

typedef struct s_table
{
	t_philo				*philo;
	atomic_int			nb_philo;
	atomic_int			nb_of_times_each_philo_must_eat;
	unsigned long		time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	long				start_time;
	int 				dinner_in_progress;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		death;
}	t_table;

/* -Main- */
unsigned long	get_time_now(void);
void			print_log(t_philo *philo, char *str);

/* -Actions- */
void			ft_action(t_table *table, int duration);
void			eat_and_sleep(t_philo *philo, int phi_id, int next);
void			check_if_someone_died(t_table *table);

/* -Initialize- */
bool			protect_and_init(t_table *table, char **av, int ac);

/* -Mutexes and threads- */
bool			ft_create_mutexes(t_table *table);
bool			ft_create_threads(t_table *table);

/* -Philo- */
int				run_philo_loop(t_table *table);

/* -Utils- */
bool			print_error(char *str);
bool			ft_isdigit(char *str);
int				ft_atoi(const char *str);

#endif
