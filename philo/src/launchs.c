/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:43:59 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/03 11:04:25 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	watcher_error(t_philo *table, t_rules *rules);
static void	philo_launch_error(int i, t_philo *table, t_rules *rules);

int	launch_philos(t_philo *table, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nbr)
	{
		if (pthread_create(&table[i].thread_id, NULL, routine, &table[i]))
		{
			philo_launch_error(i, table, rules);
			return (1);
		}
		i++;
	}
	return (0);
}

int	watch(t_philo *table, t_rules *rules)
{
	pthread_t	watcher_id;

	if (pthread_create(&watcher_id, NULL, watcher_routine, (void *)table))
	{
		watcher_error(table, rules);
		return (1);
	}
	pthread_join(watcher_id, NULL);
	return (0);
}

void	wait_philos(t_philo *table)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = table->rules->nbr;
	while (i < nbr)
	{
		pthread_join(table[i].thread_id, NULL);
		i++;
	}
}

static void	watcher_error(t_philo *table, t_rules *rules)
{
	simulation_done(table, 0, 0);
	clean_all(table, rules);
}

static void	philo_launch_error(int i, t_philo *table, t_rules *rules)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_lock(&table[j].done_mutex);
		table[j].is_done = 1;
		pthread_mutex_unlock(&table[j].done_mutex);
		j++;
	}
	j = 0;
	while (j < i)
	{
		pthread_join(table[j].thread_id, NULL);
		j++;
	}
	clean_all(table, rules);
}
