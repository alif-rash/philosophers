/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:22:53 by raalifa           #+#    #+#             */
/*   Updated: 2025/09/17 16:22:53 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_validate_range(char **av)
{
	if (ft_atoi(av[1]) > 200)
	{
		printf("Error: Number of philosophers must be 1-200\n");
		return (0);
	}
	if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
	{
		printf("Error: Time values must be at least 60ms\n");
		return (0);
	}
	if (av[5] && ft_atoi(av[5]) <= 0)
	{
		printf("Error: Number of meals must be positive\n");
		return (0);
	}
	return (1);
}

int	ft_validate_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo <philos> <die> <eat> <sleep> [meals]\n");
		return (0);
	}
	i = 1;
	while (i < ac)
	{
		if (!ft_is_numeric(av[i]) || ft_atoi(av[i]) <= 0)
		{
			printf("Error: Argument %d must be a positive integer\n", i);
			return (0);
		}
		i++;
	}
	if (!ft_validate_range(av))
		return (0);
	return (1);
}
