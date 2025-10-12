/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:23:31 by raalifa           #+#    #+#             */
/*   Updated: 2025/10/12 10:23:31 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (!ft_validate_args(ac, av))
		return (1);
	if (init_data(&data, av) != 0)
	{
		printf("Error: Data initialization failed\n");
		return (1);
	}
	if (init_philos(&data) != 0)
	{
		printf("Error: Philosopher initialization failed\n");
		cleanup_all(&data);
		return (1);
	}
	if (start_simulation(&data) != 0)
	{
		cleanup_all(&data);
		return (1);
	}
	cleanup_all(&data);
	return (0);
}
