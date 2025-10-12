/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:23:59 by raalifa           #+#    #+#             */
/*   Updated: 2025/10/12 10:23:59 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!check_death(philo->data))
	{
		philo_eat(philo);
		if (philo->data->meals_required != -1
			&& philo->meals_eaten >= philo->data->meals_required)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

/** Checks if philosopher has died due to starvation */
static int	check_philosopher_death(t_philo *philo)
{
	long	current_time;
	long	time_since_meal;

	pthread_mutex_lock(&philo->data->meal_lock);
	current_time = get_cur_time();
	time_since_meal = current_time - philo->last_meal_time;
	if (time_since_meal >= philo->data->time_to_die && !philo->eating)
	{
		pthread_mutex_unlock(&philo->data->meal_lock);
		set_death(philo->data);
		pthread_mutex_lock(&philo->data->write_lock);
		printf("%ld %d died\n", current_time - philo->data->start_time,
			philo->id);
		pthread_mutex_unlock(&philo->data->write_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (0);
}

/// Verifies if all philosophers have eaten the required number of meals
static int	check_all_ate(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->meals_required == -1)
		return (0);
	all_ate = 1;
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (data->philos[i].meals_eaten < data->meals_required)
			all_ate = 0;
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	if (all_ate)
		set_death(data);
	return (all_ate);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!check_death(data))
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (check_philosopher_death(&data->philos[i]))
				return (NULL);
			i++;
		}
		if (check_all_ate(data))
			return (NULL);
		ft_usleep(1);
	}
	return (NULL);
}
