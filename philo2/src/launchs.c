/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:43:59 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/02 15:59:12 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	launch_philos(t_philo *table, t_rules *rules)
{
	int i;
	
	i = 0;
	while (i < rules->nbr)
	{	
		if (pthread_create(&table[i].thread_id, NULL, routine, &table[i]))
		{	
			// finish_and_quit(i, table);
			return (1);
		}
		i++;
	}
	return (0);
}
int	watch(t_philo *table, t_rules *rules)
{
	pthread_t	watcher_id;
	
	(void)rules;
	if (pthread_create(&watcher_id, NULL, watcher_routine, (void *)table))
	{	
		// clean_all_threads(table);
		return (1);
	}
	pthread_join(watcher_id, NULL);
	return (0);
}


void	wait_philos(t_philo *table)
{
	int i;
	int	nbr;
	
	i = 0;
	nbr = table->rules->nbr;
	while (i < nbr)
	{
		pthread_join(table[i].thread_id, NULL);
		i++;
	}
}