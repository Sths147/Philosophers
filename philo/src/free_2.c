/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:55:30 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/03 10:48:12 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_all(t_philo *table, t_rules *rules)
{
	clean_philos(table, rules);
	clean_rules(rules);
}

void	clean_rules(t_rules *rules)
{
	pthread_mutex_destroy(&rules->isdone_mutex);
	pthread_mutex_destroy(&rules->mutex_printf);
	clean_forks(rules->forks, rules->nbr);
	free(rules);
}

void	clean_forks(t_fork *forks, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
		pthread_mutex_destroy(&forks[i].fork);
	free(forks);
}

void	clean_philos(t_philo *table, t_rules *rules)
{
	int i;
	int nbr;

	nbr = rules->nbr;
	i = 0;
	while (i < nbr)
	{
		pthread_mutex_destroy(&table[i].done_mutex);
		pthread_mutex_destroy(&table[i].stamp_mutex);
		pthread_mutex_destroy(&table[i].meals_mutex);
		i++;
	}
	free(table);
}