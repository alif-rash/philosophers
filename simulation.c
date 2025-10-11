/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 00:00:00 by raalifa           #+#    #+#             */
/*   Updated: 2025/10/11 00:00:00 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*@brief Creates threads for philosophers and monitor*/
static int	create_threads(t_data *data, pthread_t *monitor)
{
	int	i;

	if (pthread_create(monitor, NULL, monitor_routine, data) != 0)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

/* Joins all philosopher threads and monitor thread */
static int	join_threads(t_data *data, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	return (0);
}

/* Starts the dining philosophers simulation */
int	start_simulation(t_data *data)
{
	pthread_t	monitor;

	if (create_threads(data, &monitor) != 0)
	{
		printf("Error: Thread creation failed\n");
		return (1);
	}
	if (join_threads(data, monitor) != 0)
	{
		printf("Error: Thread join failed\n");
		return (1);
	}
	return (0);
}
