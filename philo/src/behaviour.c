/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:40:59 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/05 15:53:21 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	actual_time(t_args rules)
{
	struct timeval	tv;
	time_t			result;

	(void)rules;
	gettimeofday(&tv, NULL);
	
	result = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - rules.beg_time;
	return (result);
}

void	feed_last_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork.mutex);
	pthread_mutex_lock(&(philo - philo->args.nbr)->fork.mutex);
	philo->thinks = 0;
	philo->eats = 1;
	printf("%zu %d is eating\n", actual_time(philo->args), philo->philo_nbr);
	philo->last_meal_stamp = actual_time(philo->args);
	usleep(philo->args.eat_clock);
	pthread_mutex_unlock(&philo->fork.mutex);
	pthread_mutex_unlock(&(philo - philo->args.nbr)->fork.mutex);
}

void	feed_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork.mutex);
	pthread_mutex_lock(&(philo + 1)->fork.mutex);
	philo->thinks = 0;
	philo->eats = 1;
	printf("%zu %d is eating\n", actual_time(philo->args), philo->philo_nbr);
	philo->last_meal_stamp = actual_time(philo->args);
	usleep(philo->args.eat_clock);
	pthread_mutex_unlock(&philo->fork.mutex);
	pthread_mutex_unlock(&(philo + 1)->fork.mutex);
}

void *routine(void *args)
{
	t_philo			*philo;
	int				i;
	
	philo = (t_philo *)args;
	i = 0;
	while (1)
	{
		if (actual_time(philo->args) > philo->args.death_clock + philo->last_meal_stamp)
			break ;
		if (!(philo + 1) && philo->thinks) // && philo->last_meal_stamp <= (philo - philo->args.nbr)->last_meal_stamp
		{
			feed_last_philo(philo);
		}
		else if (philo->thinks && philo->last_meal_stamp <= (philo + 1)->last_meal_stamp)
			feed_philo(philo);
		if (philo->eats)
		{
			printf("%zu %d is sleeping\n", actual_time(philo->args), philo->philo_nbr);
			philo->eats = 0;
			usleep(philo->args.sleep_clock);
			philo->thinks = 1;
			printf("%zu %d is thinking\n", actual_time(philo->args), philo->philo_nbr);
			philo->last_sleep_stamp = actual_time(philo->args);
		}
	}
	return (NULL);
}
