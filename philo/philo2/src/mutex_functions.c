/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:44:10 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/03 10:52:13 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_secured(time_t time, int id, char *str, t_rules *rules)
{
	pthread_mutex_lock(&rules->mutex_printf);
	printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(&rules->mutex_printf);
}

void	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	if (philo->right_fork->is_taken == 0)
	{
		philo->right_fork->is_taken = 1;
		printf_secured(actual_time(philo->rules), philo->philo_id,
			"has taken a fork", philo->rules);
	}
	pthread_mutex_lock(&philo->left_fork->fork);
	if (philo->left_fork->is_taken == 0)
	{
		philo->left_fork->is_taken = 1;
		printf_secured(actual_time(philo->rules), philo->philo_id,
			"has taken a fork", philo->rules);
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->right_fork->fork);
	philo->right_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->left_fork->fork);
	philo->left_fork->is_taken = 0;
}

void	actualise_meal_stamp(t_philo *philo)
{
	pthread_mutex_lock(&philo->stamp_mutex);
	philo->last_meal_stamp = actual_time(philo->rules);
	pthread_mutex_unlock(&philo->stamp_mutex);
}

int	is_it_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->done_mutex);
	if (philo->is_done)
	{
		pthread_mutex_unlock(&philo->done_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->done_mutex);
	return (0);
}
