/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:23:44 by raalifa           #+#    #+#             */
/*   Updated: 2025/10/12 10:23:44 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define MAX_PHILOS 200

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				eating;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				someone_died;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philos;
}	t_data;

/*
** ============================================================================
** PARSING & VALIDATION
** ============================================================================
*/

/* Validates command-line arguments */
int		ft_validate_args(int ac, char **av);
/* Checks if string contains only numeric characters */
int		ft_is_numeric(char *str);
/* Converts string to long with overflow protection */
long	ft_atoi(char *str);

/*
** ============================================================================
** INITIALIZATION & CLEANUP
** ============================================================================
*/

/* Initializes simulation data from arguments */
int		init_data(t_data *data, char **av);
/* Initializes philosopher array and assigns forks */
int		init_philos(t_data *data);
/* Cleans up all resources and destroys mutexes */
void	cleanup_all(t_data *data);

/*
** ============================================================================
** SIMULATION & THREADS
** ============================================================================
*/

/* Starts simulation by creating threads */
int		start_simulation(t_data *data);
/* Main routine for each philosopher thread */
void	*philosopher_routine(void *arg);
/* Monitor thread checks for death/completion */
void	*monitor_routine(void *arg);

/*
** ============================================================================
** TIME UTILITIES
** ============================================================================
*/

/* Gets current time in milliseconds */
long	get_cur_time(void);
/* Custom sleep with precise timing */
void	ft_usleep(long milliseconds);
/* Prints philosopher status (thread-safe) */
void	print_status(t_philo *philo, char *status);

/*
** ============================================================================
** SYNCHRONIZATION
** ============================================================================
*/

/* Checks if someone died (thread-safe) */
int		check_death(t_data *data);
/* Sets death flag (thread-safe) */
void	set_death(t_data *data);

/*
** ============================================================================
** PHILOSOPHER ACTIONS
** ============================================================================
*/

/* Philosopher eating action */
void	philo_eat(t_philo *philo);
/* Philosopher sleeping action */
void	philo_sleep(t_philo *philo);
/* Philosopher thinking action */
void	philo_think(t_philo *philo);

#endif