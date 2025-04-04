/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:43:42 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/04 12:54:33 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		init_rules_mutexes(t_rules *rules);
static t_fork	*init_fork_array(t_rules *rules);
static int		init_forks_and_time(t_rules *result);

t_rules	*init_rules(int ac, char **av)
{
	t_rules	*result;

	result = (t_rules *)malloc(sizeof(t_rules));
	if (!result)
		return (NULL);
	result->nbr = ft_atoi(av[1]);
	result->die_time = (time_t)ft_atoi(av[2]);
	result->eat_time = (time_t)ft_atoi(av[3]);
	result->sleep_time = (time_t)ft_atoi(av[4]);
	if (ac == 6)
		result->meals_nbr = ft_atoi(av[5]);
	else
		result->meals_nbr = -1;
	if (init_rules_mutexes(result))
	{
		free(result);
		return (NULL);
	}
	if (init_forks_and_time(result))
		return (NULL);
	return (result);
}

static int	init_forks_and_time(t_rules *result)
{
	struct timeval	tv;

	result->forks = init_fork_array(result);
	if (result->forks == NULL)
	{
		destroy_rules(result);
		return (1);
	}
	gettimeofday(&tv, NULL);
	result->beg_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000) + (result->nbr
			* 100);
	return (0);
}

static int	init_rules_mutexes(t_rules *rules)
{
	if (pthread_mutex_init(&rules->mutex_printf, NULL))
	{
		free(rules);
		return (1);
	}
	if (pthread_mutex_init(&rules->isdone_mutex, NULL))
	{
		pthread_mutex_destroy(&rules->mutex_printf);
		free(rules);
		return (1);
	}
	return (0);
}

static t_fork	*init_fork_array(t_rules *rules)
{
	t_fork	*result;
	int		i;

	result = (t_fork *)malloc(rules->nbr * sizeof(t_fork));
	if (!result)
	{
		destroy_rules(rules);
		return (NULL);
	}
	i = 0;
	while (i < rules->nbr)
	{
		result[i].is_taken = 0;
		if (pthread_mutex_init(&result[i].fork, NULL))
		{
			kill_ongoing_fork_array(result, i - 1);
			destroy_rules(rules);
			return (NULL);
		}
		i++;
	}
	return (result);
}
