/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:50:32 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/05 15:54:54 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

t_philo	*init_philo(t_args rules);

/*
What cases:
	- If thinks & fork + fork+1 is free-> eats
	- if actual time > last_meal+deathclock -> DIE
	- if eats --> 
	
	if eats

*/

int	main(int ac, char **av)
{
	t_args		rules;
	int			i;
	t_philo		*philo_array;
	
	if (ac != 5 && ac != 6)
		return (0);
	// if (!check_args)
	// 	return (ERROR)
	rules = init_rules(ac, av);
	philo_array = init_philo(rules);
	i = 0;
	while (i < rules.nbr)
	{
		if (pthread_create(&philo_array[i].thread_id, NULL, routine, &philo_array[i]))
			return (perror("pthread create"), 1);
		i++;
	}
	i = 0;
	while (i < rules.nbr)
	{
		if (pthread_join(philo_array[i].thread_id, NULL))
			return 1; //ERROR
		i++;
	}
	//free_tab(thread_array);
	return (0);
}

/*
What do I need to do 
MANDATORY
create as many threads as number of philosophers
each thread has as argument a struct of 

*/