/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:40:59 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/21 16:25:25 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

int	feed_last_philo(t_philo *philo);
int	feed_philo(t_philo *philo);
int	routine_philo(t_philo *philo);
int	routine_last_philo(t_philo *philo);

void *routine(void *args)
{
	t_philo			*philo;
	
	philo = (t_philo *)args;
	while (get_time() < philo->args.beg_time)
		continue ;
	if (philo->philo_nbr % 2)
		usleep(100);
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
	printf_secured(actual_time(philo->args), philo->philo_nbr, "has taken a fork", philo->printf_mutex);
	pthread_mutex_lock(&philo->forks[0]);
	printf_secured(actual_time(philo->args), philo->philo_nbr, "has taken a fork", philo->printf_mutex);
	philo->thinks = 0;
	philo->eats = 1;
	philo->last_meal_stamp = actual_time(philo->args);
	printf_secured(actual_time(philo->args), philo->philo_nbr, "is eating", philo->printf_mutex);
	myusleep(philo->args.eat_clock, philo);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->forks[philo->philo_nbr - 1]);
	pthread_mutex_unlock(&philo->forks[0]);
	if (isdone(philo->args))
		return (1);
	return (0);
}

int	feed_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->philo_nbr - 1]);
	printf_secured(actual_time(philo->args), philo->philo_nbr, "has taken a fork", philo->printf_mutex);
	pthread_mutex_lock(&philo->forks[philo->philo_nbr]);
	printf_secured(actual_time(philo->args), philo->philo_nbr, "has taken a fork", philo->printf_mutex);
	philo->thinks = 0;
	philo->eats = 1;
	philo->last_meal_stamp = actual_time(philo->args);
	printf_secured(actual_time(philo->args), philo->philo_nbr, "is eating", philo->printf_mutex);
	myusleep(philo->args.eat_clock, philo);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->forks[philo->philo_nbr - 1]);
	pthread_mutex_unlock(&philo->forks[philo->philo_nbr]);
	if (isdone(philo->args))
		return (1);
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
			printf_secured(actual_time(philo->args), philo->philo_nbr, "is sleeping", philo->printf_mutex);
			philo->eats = 0;
			usleep(philo->args.sleep_clock * 1000);
			philo->thinks = 1;
			printf_secured(actual_time(philo->args), philo->philo_nbr, "is thinking", philo->printf_mutex);
		}
		usleep(100);
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
			printf_secured(actual_time(philo->args), philo->philo_nbr, "is sleeping", philo->printf_mutex);			
			philo->eats = 0;
			usleep(philo->args.sleep_clock * 1000);
			philo->thinks = 1;
			printf_secured(actual_time(philo->args), philo->philo_nbr, "is thinking", philo->printf_mutex);			
		}
		usleep(100);
	}
	return (0);
}
