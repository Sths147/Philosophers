/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:03:58 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/03 10:48:08 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Destroys rules and the fork array until an index
*/

void	destroy_rules_2(t_rules *rules)
{
	kill_ongoing_fork_array(rules->forks, rules->nbr - 1);
	destroy_rules(rules);
}

void	destroy_rules(t_rules *rules)
{
	pthread_mutex_destroy(&rules->isdone_mutex);
	pthread_mutex_destroy(&rules->mutex_printf);
	free(rules);
}

void	kill_ongoing_fork_array(t_fork *result, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&result->fork);
		i--;
	}
	free(result);
}

void	free_mutexes_philo(t_philo *table, int i, int stamp)
{
	if (stamp == 2)
		pthread_mutex_destroy(&table[i].done_mutex);
	if (stamp)
		pthread_mutex_destroy(&table[i].stamp_mutex);
	i--;
	while (i >= 0)
	{
		pthread_mutex_destroy(&table[i].stamp_mutex);
		pthread_mutex_destroy(&table[i].meals_mutex);
		pthread_mutex_destroy(&table[i].done_mutex);
		i--;
	}
}