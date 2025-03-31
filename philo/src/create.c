/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:30:14 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/31 17:30:51 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


t_philo	init_single_philo(t_args *rules, pthread_mutex_t *fork_array, int i)
{
	t_philo	result;

	result.philo_nbr = i + 1;
	result.args = rules;
	result.last_meal_stamp = 0;
	result.eats = 0;
	result.thinks = 1;
	result.sleeps = 0;
	result.is_dead = 0;
	result.started = 0;
	result.forks = fork_array;
	result.meals_eaten = 0;
	result.ate_mutex = malloc(sizeof(pthread_mutex_t));
	if (!result.ate_mutex)
		exit(1);//free all
	if (pthread_mutex_init(result.ate_mutex, NULL) == -1)
		exit(1);//free all
	result.stamp_mutex = malloc(sizeof(pthread_mutex_t));
	if (!result.stamp_mutex)
		exit(1);//free all
	if (pthread_mutex_init(result.stamp_mutex, NULL) == -1)
		exit(1);//free all
	return (result);
}

t_philo	*init_philo(t_args *rules, pthread_mutex_t *fork_array)
{
	t_philo					*philo_array;
	int						i;

	philo_array = (t_philo *)malloc(rules->nbr * sizeof(t_philo));
	if (!philo_array)
		return (NULL);
	i = 0;
	while (i < rules->nbr)
	{
		philo_array[i] = init_single_philo(rules, fork_array, i);
		i++;
	}
	usleep(100);
	return (philo_array);
}
