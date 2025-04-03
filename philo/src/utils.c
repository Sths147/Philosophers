/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:15:38 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/03 10:45:29 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (av[i])
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

time_t	actual_time(t_rules *rules)
{
	struct timeval	tv;
	time_t			result;

	gettimeofday(&tv, NULL);
	result = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - rules->beg_time;
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

int	special_cases(char **av)
{
	if (av[1][0] == '0' && !av[1][1])
		return (1);
	if (av[1][0] == '1' && !av[1][1])
	{
		printf("0 1 has taken a fork\n");
		usleep((ft_atoi(av[2]) + 1) * 1000);
		printf("%d is dead\n", ft_atoi(av[2]) + 1);
		return (1);
	}
	return (0);
}
