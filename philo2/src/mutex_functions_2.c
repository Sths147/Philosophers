/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:54:57 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/01 18:43:17 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	myusleep(int time, t_philo *philo)
{
	time_t	start;

	start = get_time();
	while (get_time() < start + time && !is_it_done(philo))
		usleep(100);
}

void	update_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_mutex);
}
