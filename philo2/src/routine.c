/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:20:47 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/01 18:43:46 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	feed_philo(t_philo *philo);

void *routine(void *args)
{
	t_philo			*philo;
	
	philo = (t_philo *)args;
	while (get_time() < philo->rules->beg_time)
		continue ;
	if (philo->philo_id % 2)
		usleep(100);
	actualise_meal_stamp(philo);
	pthread_mutex_lock(&philo->rules->isdone_mutex);
	while (!(philo->rules->is_done))
	{
		pthread_mutex_unlock(&philo->rules->isdone_mutex);
		if (philo->eats && feed_philo(philo))
			break;
		else
		{
			printf_secured(actual_time(philo->rules), philo->philo_id, "is sleeping", philo->rules);
			philo->eats = 1;
			myusleep(philo->rules->sleep_time, philo);
			if (is_it_done(philo))
				break;
			printf_secured(actual_time(philo->rules), philo->philo_id, "is thinking", philo->rules);			
		}
		pthread_mutex_lock(&philo->rules->isdone_mutex);
	}
	pthread_mutex_lock(&philo->rules->isdone_mutex);
	return (NULL);
}

static int	feed_philo(t_philo *philo)
{
	grab_forks(philo);
	actualise_meal_stamp(philo);
	printf_secured(actual_time(philo->rules), philo->philo_id, "is eating", philo->rules);
	myusleep(philo->rules->eat_time, philo);
	if (is_it_done(philo))
		return (1);
	update_meals(philo);
	philo->eats = 0;
	drop_forks(philo);
	return (0);
}

