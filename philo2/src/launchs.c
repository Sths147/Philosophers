/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:43:59 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/01 18:08:45 by sithomas         ###   ########.fr       */
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
			return (1);
		i++;
	}
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