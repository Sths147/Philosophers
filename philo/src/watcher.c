/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:20:20 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/03 18:14:16 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meals(t_philo *philo);
static int	check_if_dead(t_philo *philo);

void	*watcher_routine(void *args)
{
	t_philo	*table;
	int		nbr;
	int		i;

	table = (t_philo *)args;
	nbr = table->rules->nbr;
	while (1)
	{
		i = -1;
		while (++i < table->rules->nbr)
		{
			if (check_if_dead(&table[i]))
			{
				simulation_done(table, i + 1, 1);
				return (NULL);
			}
			nbr += check_meals(&table[i]);
			if (nbr == 0)
			{
				simulation_done(table, i, 0);
				return (NULL);
			}
		}
	}
	return (NULL);
}

static int	check_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_mutex);
	if (philo->meals_eaten == philo->rules->meals_nbr)
	{
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meals_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->meals_mutex);
	return (0);
}

void	simulation_done(t_philo *table, int i, int type)
{
	int	j;
	int	nbr;

	j = 0;
	nbr = table->rules->nbr;
	while (j < nbr)
	{
		pthread_mutex_lock(&table[j].done_mutex);
		table[j].is_done = 1;
		pthread_mutex_unlock(&table[j].done_mutex);
		j++;
	}
	if (table->rules->nbr == 1)
	{
		pthread_mutex_lock(&table[0].right_fork->fork);
		if (table[0].right_fork->is_taken == 1)
			table[0].right_fork->is_taken = 0;
		pthread_mutex_unlock(&table[0].right_fork->fork);
	}
	wait_philos(table);
	if (type)
		printf_secured(actual_time(table->rules), i, "died", table->rules);
}

static int	check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->stamp_mutex);
	if (actual_time(philo->rules) > philo->last_meal_stamp
		+ philo->rules->die_time)
	{
		pthread_mutex_unlock(&philo->stamp_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->stamp_mutex);
	return (0);
}
