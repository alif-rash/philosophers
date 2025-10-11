/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:38:59 by raalifa           #+#    #+#             */
/*   Updated: 2025/09/12 17:38:59 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file philo.h
 * @brief Dining Philosophers Problem - Main header file
 * @author raalifa
 * @date 2025/09/12
 */

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
	int				id;              /**< Philosopher ID (1 to N) */
	int				meals_eaten;     /**< Number of meals consumed */
	int				eating;          /**< Flag: 1 if currently eating, 0 otherwise */
	long			last_meal_time;  /**< Timestamp of last meal start (ms) */
	pthread_t		thread;          /**< Thread handle for this philosopher */
	pthread_mutex_t	*left_fork;      /**< Pointer to left fork mutex */
	pthread_mutex_t	*right_fork;     /**< Pointer to right fork mutex */
	struct s_data	*data;           /**< Pointer to shared simulation data */
}	t_philo;

typedef struct s_data
{
	int				philo_count;     /**< Total number of philosophers */
	int				time_to_die;     /**< Time (ms) before a philosopher dies of starvation */
	int				time_to_eat;     /**< Time (ms) required to eat */
	int				time_to_sleep;   /**< Time (ms) spent sleeping */
	int				meals_required;  /**< Required meals per philosopher (-1 = unlimited) */
	int				someone_died;    /**< Flag: 1 if any philosopher died */
	long			start_time;      /**< Simulation start timestamp (ms) */
	pthread_mutex_t	*forks;          /**< Array of fork mutexes */
	pthread_mutex_t	write_lock;      /**< Mutex for synchronized console output */
	pthread_mutex_t	death_lock;      /**< Mutex for death flag access */
	pthread_mutex_t	meal_lock;       /**< Mutex for meal counting/timing */
	t_philo			*philos;         /**< Array of philosophers */
}	t_data;

/* ========================================================================== */
/*                            PARSING & VALIDATION                            */
/* ========================================================================== */

/**
 * @brief Validates command-line arguments
 * @param ac Argument count
 * @param av Argument vector
 * @return 1 if valid, 0 otherwise
 */
int		ft_validate_args(int ac, char **av);

/**
 * @brief Checks if a string contains only numeric characters
 * @param str String to validate
 * @return 1 if numeric, 0 otherwise
 */
int		ft_is_numeric(char *str);

/**
 * @brief Converts string to long integer with overflow protection
 * @param str String to convert
 * @return Converted long integer, or -1 on overflow
 */
long	ft_atoi(char *str);

/* ========================================================================== */
/*                         INITIALIZATION & CLEANUP                           */
/* ========================================================================== */

/**
 * @brief Initializes simulation data structure from arguments
 * @param data Pointer to data structure to initialize
 * @param av Argument vector containing simulation parameters
 * @return 0 on success, 1 on failure
 */
int		init_data(t_data *data, char **av);

/**
 * @brief Initializes philosopher array and assigns forks
 * @param data Pointer to simulation data
 * @return 0 on success, 1 on failure
 */
int		init_philos(t_data *data);

/**
 * @brief Cleans up all allocated resources and destroys mutexes
 * @param data Pointer to simulation data
 */
void	cleanup_all(t_data *data);

/* ========================================================================== */
/*                            SIMULATION CONTROL                              */
/* ========================================================================== */

/**
 * @brief Starts the simulation by creating threads
 * @param data Pointer to simulation data
 * @return 0 on success, 1 on failure
 */
int		start_simulation(t_data *data);

/**
 * @brief Main routine executed by each philosopher thread
 * @param arg Pointer to t_philo structure (philosopher data)
 * @return NULL
 */
void	*philosopher_routine(void *arg);

/**
 * @brief Monitor thread routine - checks for death and completion
 * @param arg Pointer to t_data structure (simulation data)
 * @return NULL
 */
void	*monitor_routine(void *arg);

/* ========================================================================== */
/*                             TIME UTILITIES                                 */
/* ========================================================================== */

/**
 * @brief Gets current time in milliseconds
 * @return Current timestamp in milliseconds since epoch
 */
long	get_cur_time(void);

/**
 * @brief Custom sleep function with precise timing
 * @param milliseconds Time to sleep in milliseconds
 */
void	ft_usleep(long milliseconds);

/**
 * @brief Prints philosopher status with timestamp (thread-safe)
 * @param philo Pointer to philosopher
 * @param status Status string to print (e.g., "is eating")
 */
void	print_status(t_philo *philo, char *status);

/* ========================================================================== */
/*                          SYNCHRONIZATION HELPERS                           */
/* ========================================================================== */

/**
 * @brief Safely checks if someone died (thread-safe)
 * @param data Pointer to simulation data
 * @return 1 if someone died, 0 otherwise
 */
int		check_death(t_data *data);

/**
 * @brief Sets death flag (thread-safe)
 * @param data Pointer to simulation data
 */
void	set_death(t_data *data);

/* ========================================================================== */
/*                          PHILOSOPHER ACTIONS                               */
/* ========================================================================== */

/**
 * @brief Philosopher eating action (acquires forks, eats, releases forks)
 * @param philo Pointer to philosopher
 */
void	philo_eat(t_philo *philo);

/**
 * @brief Philosopher sleeping action
 * @param philo Pointer to philosopher
 */
void	philo_sleep(t_philo *philo);

/**
 * @brief Philosopher thinking action
 * @param philo Pointer to philosopher
 */
void	philo_think(t_philo *philo);

#endif