/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 00:00:00 by raalifa           #+#    #+#             */
/*   Updated: 2025/10/11 00:00:00 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_cur_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long milliseconds)
{
	long	start;
	long	current;

	start = get_cur_time();
	while (1)
	{
		current = get_cur_time();
		if ((current - start) >= milliseconds)
			break ;
		usleep(100);
	}
}

int	check_death(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->death_lock);
	result = data->someone_died;
	pthread_mutex_unlock(&data->death_lock);
	return (result);
}

void	set_death(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_lock);
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	if (check_death(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	timestamp = get_cur_time() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->data->write_lock);
}
