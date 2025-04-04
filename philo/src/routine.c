/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:20:47 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/04 12:44:09 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	feed_philo(t_philo *philo);
static void	philo_wait(t_philo *philo);
static int	one_philo(t_philo *philo);

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo_wait(philo);
	actualise_meal_stamp(philo);
	if (philo->rules->nbr == 1 && one_philo(philo))
		return (NULL);
	while (1)
	{
		if (philo->eats && feed_philo(philo))
			break ;
		else if (philo->eats == 0)
		{
			printf_secured(actual_time(philo->rules), philo->philo_id,
				"is sleeping", philo->rules);
			if (is_it_done(philo))
				break ;
			myusleep(philo->rules->sleep_time, philo);
			philo->eats = 1;
			printf_secured(actual_time(philo->rules), philo->philo_id,
				"is thinking", philo->rules);
			usleep(100);
		}
	}
	return (NULL);
}

static int	feed_philo(t_philo *philo)
{
	if (grab_forks(philo))
	{
		if (is_it_done(philo))
		{
			drop_forks(philo);
			return (1);
		}
		actualise_meal_stamp(philo);
		printf_secured(actual_time(philo->rules), philo->philo_id, "is eating",
			philo->rules);
		myusleep(philo->rules->eat_time, philo);
		update_meals(philo);
		philo->eats = 0;
		drop_forks(philo);
	}
	return (0);
}

static void	philo_wait(t_philo *philo)
{
	while (get_time() < philo->rules->beg_time)
		continue ;
	if (philo->philo_id % 2)
		usleep(100);
}

static int	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	philo->right_fork->is_taken = 1;
	printf_secured(actual_time(philo->rules), philo->philo_id,
		"has taken a fork", philo->rules);
	while (1)
	{
		if (is_it_done(philo))
		{
			pthread_mutex_unlock(&philo->right_fork->fork);
			return (1);
		}
		myusleep(500, philo);
	}
	pthread_mutex_unlock(&philo->right_fork->fork);
	return (0);
}
