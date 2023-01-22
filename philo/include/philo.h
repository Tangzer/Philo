/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Verdoodt <Verdoodt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:56:35 by tverdood          #+#    #+#             */
/*   Updated: 2023/01/22 18:54:21 by Verdoodt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdatomic.h>
# include <stdbool.h>

# define PHILO_MAX 1000

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
	int						id_philo;
	atomic_uint_fast64_t	last_meal;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
}	t_philo;

typedef struct s_table
{
	int					error;
	int					nb_philo;
	unsigned long		time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	atomic_int			nb_times_each_philo_must_eat;
	atomic_int			nb_philo_who_ate_this_round;
	atomic_int			index;
	unsigned long		dinner_starting_time;
	atomic_int			nb_rounds;
	atomic_int			someone_dead;
	pthread_mutex_t		print;
	pthread_mutex_t		*forks;
	t_philo				**philo;
	pthread_t			*thread;
}	t_table;

/* -Main- */
unsigned long long	get_time_now(void);
void				print_log(t_table *table, t_philo *philo, int status);
bool				join_threads(t_table *table);

/* -Actions- */
void				start_eating(t_table *table, t_philo *philo);

/* -Cleaning- */
bool				free_philos(t_table *table);
bool				destroy_fork_mutexes(t_table *table);
int					free_and_exit(t_table *table, int k);
bool				destroy_print_mutex(t_table *table);

/* -Dead- */
void				check_if_someone_died(t_table *table);

/* -Forks- */
void				init_philo_forks_in_hand(t_table *table, int id);
bool				init_mutex_forks(t_table *table);

/* -Initialize- */
void				init_philo_forks_in_hand(t_table *table, int id);
t_table				*protect_and_init(char **av, int ac);

/* -Philo- */
bool				run_philo_loop(t_table *table);
void				ft_sleep(unsigned long long time_to_sleep, t_table *table);

/* -Utils- */
bool				print_error(char *str);
bool				ft_isdigit(char *str);
int					ft_atoi(const char *str);

#endif
