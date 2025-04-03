/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:16:51 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/03 11:04:13 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, int i);
static int	start_philo_mutex(t_philo *table);

t_philo	*init_philos(t_rules *rules)
{
	t_philo	*table;
	int		i;

	table = (t_philo *)malloc(rules->nbr * sizeof(t_philo));
	if (!table)
		return (NULL);
	i = 0;
	while (i < rules->nbr)
	{
		table[i].philo_id = i + 1;
		table[i].eats = 1;
		table[i].is_done = 0;
		table[i].rules = rules;
		table[i].meals_eaten = 0;
		table[i].last_meal_stamp = 0;
		assign_forks(&table[i], i);
		i++;
	}
	if (start_philo_mutex(table))
	{
		free(table);
		return (NULL);
	}
	return (table);
}

static void	assign_forks(t_philo *philo, int i)
{
	if (i == philo->rules->nbr - 1)
	{
		philo->left_fork = &philo->rules->forks[0];
		philo->right_fork = &philo->rules->forks[i];
	}
	else
	{
		philo->left_fork = &philo->rules->forks[i];
		philo->right_fork = &philo->rules->forks[i + 1];
	}
}

static int	start_philo_mutex(t_philo *table)
{
	int	i;

	i = 0;
	while (i < table->rules->nbr)
	{
		if (pthread_mutex_init(&table[i].stamp_mutex, NULL) == -1)
		{
			free_mutexes_philo(table, i, 0);
			return (1);
		}
		if (pthread_mutex_init(&table[i].meals_mutex, NULL) == -1)
		{
			free_mutexes_philo(table, i, 1);
			return (1);
		}
		if (pthread_mutex_init(&table[i].done_mutex, NULL) == -1)
		{
			free_mutexes_philo(table, i, 2);
			return (1);
		}
		i++;
	}
	return (0);
}
