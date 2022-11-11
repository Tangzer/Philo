
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

enum e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	UNLOCK,
	LOCK
};

typedef struct s_philo
{
	int					id_philo;
	unsigned long long	last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t 	*right_fork;
	pthread_t 			thread;
}	t_philo;

typedef struct s_table
{
	int					nb_philo;
	unsigned long					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_times_each_philo_must_eat;
	int 				nb_philo_who_ate_this_round;
	int					nb_rounds;
	unsigned long		dinner_starting_time;
	atomic_int			someone_dead;
	atomic_int 			dinner_in_progress;
	pthread_mutex_t 	print;
	pthread_mutex_t 	*forks;
	t_philo 			*philo;
}	t_table;

/* -Main- */
unsigned long long	get_time_now(void);
void				ft_sleep(unsigned long long time_to_sleep);
void				print_log(t_table *table, t_philo *philo, int status);

/* -Actions- */
void				start_eating(t_table *table, t_philo *philo);

/* -Dead- */
void				check_if_someone_died(t_table *table);

/* -Initialize- */
void				init_philo_forks_in_hand(t_table *table, int id);
bool				protect_and_init(t_table *table, char **av, int ac);

/* -Philo- */
bool					run_philo_loop(t_table *table);

/* -Utils- */
bool				print_error(char *str);
bool				ft_isdigit(char *str);
int					ft_atoi(const char *str);

#endif
