/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:23:21 by raalifa           #+#    #+#             */
/*   Updated: 2025/10/12 10:23:21 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Initializes mutexes for forks and other shared resources */
static int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (1);
	return (0);
}

/*Initializes the data structure with command line arguments  */
int	init_data(t_data *data, char **av)
{
	data->philo_count = (int)ft_atoi(av[1]);
	data->time_to_die = (int)ft_atoi(av[2]);
	data->time_to_eat = (int)ft_atoi(av[3]);
	data->time_to_sleep = (int)ft_atoi(av[4]);
	if (av[5])
		data->meals_required = (int)ft_atoi(av[5]);
	else
		data->meals_required = -1;
	data->someone_died = 0;
	data->start_time = get_cur_time();
	data->philos = NULL;
	data->forks = NULL;
	if (init_mutexes(data) != 0)
		return (1);
	return (0);
}

/*  Assigns forks to a philosopher */
static void	assign_forks(t_philo *philo, t_data *data, int i)
{
	philo->left_fork = &data->forks[i];
	philo->right_fork = &data->forks[(i + 1) % data->philo_count];
}

/* Initializes philosophers data structures and 
allocates necessary memory*/
int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].eating = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
		assign_forks(&data->philos[i], data, i);
		i++;
	}
	return (0);
}

/** Performs cleanup operations and frees 
 * all allocated resources in the data structure */
void	cleanup_all(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->meal_lock);
	if (data->philos)
		free(data->philos);
}
