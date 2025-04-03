/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:15:38 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/03 13:13:50 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_length(char **av);

int	ft_atoi(const char *nptr)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - 48;
		i++;
	}
	if (result > __INT_MAX__)
		return (-1);
	return (result);
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
		if (!av[i] || ft_strlen(av[i]) > 10)
			return (1);
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	if (ft_atoi(av[1]) == 0 || check_length(av))
		return (1);
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

static int	check_length(char **av)
{
	int		i;

	i = 0;
	while (av[++i])
		if (ft_atoi(av[i]) == -1)
			return (1);
	return (0);
}
