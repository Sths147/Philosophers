/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:40:59 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/13 17:33:51 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	feed_last_philo(t_philo *philo);
int	feed_philo(t_philo *philo);
int	routine_philo(t_philo *philo);
int	routine_last_philo(t_philo *philo);

void *routine(void *args)
{
	t_philo			*philo;
	int				i;
	
	philo = (t_philo *)args;
	i = 0;
	philo->last_meal_stamp = actual_time(philo->args);
	if (philo->philo_nbr == philo->args.nbr && routine_last_philo(philo))
		return (NULL);
	else if (routine_philo(philo))
		return (NULL);
	return (NULL);
}

int	feed_last_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->philo_nbr - 1]);
	printf("%zu %d has taken a fork\n", actual_time(philo->args), philo->philo_nbr);
	pthread_mutex_lock(&philo->forks[0]);
	printf("%zu %d has taken a fork\n", actual_time(philo->args), philo->philo_nbr);;
	philo->thinks = 0;
	philo->eats = 1;
	philo->last_meal_stamp = actual_time(philo->args);
	printf("%zu %d is eating\n", philo->last_meal_stamp, philo->philo_nbr);
	usleep(philo->args.eat_clock * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->forks[philo->philo_nbr - 1]);
	pthread_mutex_unlock(&philo->forks[0]);
	return (0);
}

int	feed_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->philo_nbr - 1]);
	printf("%zu %d has taken a fork\n", actual_time(philo->args), philo->philo_nbr);
	pthread_mutex_lock(&philo->forks[philo->philo_nbr]);
	printf("%zu %d has taken a fork\n", actual_time(philo->args), philo->philo_nbr);
	philo->thinks = 0;
	philo->eats = 1;
	philo->last_meal_stamp = actual_time(philo->args);
	printf("%zu %d is eating\n", philo->last_meal_stamp, philo->philo_nbr);
	usleep(philo->args.eat_clock * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->forks[philo->philo_nbr - 1]);
	pthread_mutex_unlock(&philo->forks[philo->philo_nbr]);
	return (0);
}

int	routine_philo(t_philo *philo)
{
	while (1)
	{
		if (philo->thinks && feed_philo(philo))
			return (1);
		else if (philo->eats)
		{
			printf("%zu %d is sleeping\n", actual_time(philo->args), philo->philo_nbr);
			philo->eats = 0;
			usleep(philo->args.sleep_clock * 1000);
			philo->thinks = 1;
			printf("%zu %d is thinking\n", actual_time(philo->args), philo->philo_nbr);
		}
	}
	return (0);
}

int	routine_last_philo(t_philo *philo)
{
	while (1)
	{
		if (philo->thinks && (philo->philo_nbr == philo->args.nbr) && feed_last_philo(philo))
			return (1);
		else if (philo->eats)
		{
			printf("%zu %d is sleeping\n", actual_time(philo->args), philo->philo_nbr);
			philo->eats = 0;
			usleep(philo->args.sleep_clock * 1000);
			philo->thinks = 1;
			printf("%zu %d is thinking\n", actual_time(philo->args), philo->philo_nbr);
		}
	}
	return (0);
}
