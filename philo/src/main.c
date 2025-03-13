/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:50:32 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/13 17:31:44 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
/*
What cases:
	- If thinks & fork + fork+1 is free-> eats
	- if actual time > last_meal+deathclock -> DIE
	- if eats --> 
	
	if eats

*/

int	main(int ac, char **av)
{
	t_args				rules;
	int					i;
	t_philo				*philo_array;
	pthread_mutex_t		*forks;
	int					nbr;
	
	if (ac != 5 && ac != 6)
		return (0);
	// if (!check_args)
	// 	return (ERROR)
	rules = init_rules(ac, av);
	forks = init_forks(rules);
	philo_array = init_philo(rules, forks);
	i = 0;
	while (i < rules.nbr)
	{
		if (i % 2)
			usleep(100);
		if (pthread_create(&philo_array[i].thread_id, NULL, routine, &philo_array[i]))
			return (perror("pthread create"), 1);
		printf("Thread number %lu of whith philosopher id %d created\n", philo_array[i].thread_id, philo_array[i].philo_nbr);
		i++;
	}
	nbr = rules.nbr;
	while (1)
	{
		i = -1;
		while (++i < rules.nbr)
		{
			if (actual_time(rules) > rules.death_clock + philo_array[i].last_meal_stamp)
				exit(printf("%zu %d died\n", actual_time(rules), philo_array[i].philo_nbr));
			if (philo_array[i].meals_eaten == rules.meal_nbr)	
				nbr--;
			if (nbr == 0)
				exit(printf("All philosophers ate enough\n"));
		}
	}
	// i = 0;
	// while (i < rules.nbr)
	// {
	// 	if (pthread_join(philo_array[i].thread_id, NULL))
	// 		return 1; //ERROR
	// 	i++;
	// }
	// printf("all philosophers ate enough\n");
	//free_tab(thread_array);
	return (0);
}
