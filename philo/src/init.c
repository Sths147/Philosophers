/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:58:24 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/05 15:12:06 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

t_args	init_rules(int ac, char **av)
{
	t_args	rules;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	rules.beg_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("beg time %zu\n", rules.beg_time);
	rules.nbr = ft_atoi(av[1]);
	rules.death_clock = (time_t)ft_atoi(av[2]);
	rules.eat_clock = (time_t)ft_atoi(av[3]);
	rules.sleep_clock = (time_t)ft_atoi(av[4]);
	if (ac == 6)
		rules.meal_nbr = ft_atoi(av[5]);
	return (rules);
}

t_philo	*init_philo(t_args rules)
{
	t_philo					*philo_array;
	int						i;

	philo_array = (t_philo *)malloc(rules.nbr * sizeof(t_philo));
	if (!philo_array)
		return (NULL);
	i = 0;
	while (i < rules.nbr)
	{
		philo_array[i].philo_nbr = i + 1;
		philo_array[i].args = rules;
		philo_array[i].last_meal_stamp = 0;
		philo_array[i].eats = 0;
		philo_array[i].thinks = 1;
		philo_array[i].sleeps = 0;
		philo_array[i].is_dead = 0;
		philo_array[i].fork.fork_id = i + 1;
		if (pthread_mutex_init(&philo_array[i].fork.mutex, NULL))
			return(NULL);//free all tab and return null
		i++;
	}
	return (philo_array);
}