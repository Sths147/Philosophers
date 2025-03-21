/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:00:26 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/21 15:58:50 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	actual_time(t_args rules)
{
	struct timeval	tv;
	time_t			result;

	gettimeofday(&tv, NULL);
	result = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - rules.beg_time;
	return (result);
}

time_t	get_time(void)
{
	struct timeval	tv;
	time_t			result;

	gettimeofday(&tv, NULL);
	result = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (result);
}

size_t	atosize_t(const char *nptr)
{
	int		i;
	size_t	result;

	i = 0;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - 48;
		i++;
	}
	return (result);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - 48;
		i++;
	}
	return (result * sign);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;
	
	if (ac != 5 && ac != 6)
		return (1);
	i = 1;
	while(av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	myusleep(int time, t_philo *philo)
{
	time_t	start;

	start = get_time();
	while (get_time() < start + time && philo->args.isdone == 0)
		usleep(100);
}

int		isdone(t_args	arg)
{
	pthread_mutex_lock(arg.done_mutex);
	if (arg.isdone)
	{	
		pthread_mutex_unlock(arg.done_mutex);
		return (1);
	}
	pthread_mutex_unlock(arg.done_mutex);
	return (0);
}
