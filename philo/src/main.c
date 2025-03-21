/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:50:32 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/21 16:17:11 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

/*
What cases:
	- If thinks & fork + fork+1 is free-> eats
	- if actual time > last_meal+deathclock -> DIE
	- if eats --> 
*/

static void	init_threads(t_philo *philo_array, t_args rules);
static void	end_philo_died(t_args rules, t_philo *philo_array, pthread_mutex_t *forks);
static void	all_philo_ate(t_args rules, t_philo *philo_array, pthread_mutex_t *forks);

int	main(int ac, char **av)
{
	t_args				rules;
	int					i;
	t_philo				*philo_array;
	pthread_mutex_t		*forks;
	int					nbr;
	
	if (check_args(ac, av))
		return (printf("Wrong arguments :( \n"));
	rules = init_rules(ac, av);
	forks = init_forks(rules);
	philo_array = init_philo(rules, forks);
	init_threads(philo_array, rules);
	nbr = rules.nbr;
	while (1)
	{
		i = -1;
		while (++i < rules.nbr)
		{
			if (actual_time(rules) > philo_array[i].last_meal_stamp + rules.death_clock)
				end_philo_died(rules, philo_array, forks);
			if (philo_array[i].meals_eaten == rules.meal_nbr)	
				nbr--;
			if (nbr == 0)
				all_philo_ate(rules, philo_array, forks);
		}
	}
	return (0);
}

static void	init_threads(t_philo *philo_array, t_args rules)
{
	int i;
	
	i = 0;
	while (i < rules.nbr)
	{	
		if (pthread_create(&philo_array[i].thread_id, NULL, routine, &philo_array[i]))
			return (perror("pthread create"));
		i++;
		usleep(100);
	}
}

static void	end_philo_died(t_args rules, t_philo *philo_array, pthread_mutex_t *forks)
{
	int i;
	
	i = 0;
	printf_secured(actual_time(rules), philo_array[i].philo_nbr, "died", philo_array[i].printf_mutex);
	pthread_mutex_lock(rules.done_mutex);
	rules.isdone = 1;
	pthread_mutex_unlock(rules.done_mutex);
	// while (i < rules.nbr)
	// {
	// 	pthread_join(philo_array[i].thread_id, NULL);
	// 	i++;
	// }
	free(philo_array);
	free_mutex(forks, rules.nbr);
	exit(EXIT_SUCCESS);
}

static void	all_philo_ate(t_args rules, t_philo *philo_array, pthread_mutex_t *forks)
{
	int	i;
	
	pthread_mutex_lock(rules.done_mutex);
	rules.isdone = 1;
	pthread_mutex_unlock(rules.done_mutex);
	i = 0;
	// while (i < rules.nbr)
	// {
	// 	pthread_join(philo_array[i].thread_id, NULL);
	// 	i++;
	// }
	free(philo_array);
	free_mutex(forks, rules.nbr);
	exit(printf("All philosophers ate enough\n"));
}