/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:58:24 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/21 16:29:14 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

pthread_mutex_t	*init_forks(t_args rules)
{
	pthread_mutex_t	*result;
	int		i;

	i = -1;
	result = (pthread_mutex_t *)malloc(rules.nbr * sizeof(pthread_mutex_t));
	if (!result)
		return (NULL);
	while (++i < rules.nbr)
	{
		if (pthread_mutex_init(&result[i], NULL) == -1)
			return (NULL);
	}
	return (result);
}

pthread_mutex_t	*init_printf(void)
{
	pthread_mutex_t	*print;

	print = malloc(sizeof(pthread_mutex_t));
	if (!print)
		return (NULL);
	if (pthread_mutex_init(print, NULL) == -1)
		return (NULL);
	return (print);
}

void	printf_secured(time_t time, int id, char *str, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(mutex);	
}

t_args	init_rules(int ac, char **av)
{
	t_args	rules;
	struct timeval tv;
	pthread_mutex_t	*donemutex;
	
	donemutex = malloc(sizeof(pthread_mutex_t));
	if (!donemutex)
		exit (1); //free all
	if (pthread_mutex_init(donemutex, NULL) == -1)
		exit(1); //free all
	gettimeofday(&tv, NULL);
	rules.print_mutex = init_printf();
	rules.nbr = ft_atoi(av[1]);
	rules.beg_time = tv.tv_sec * 1000 + tv.tv_usec / 1000 + (rules.nbr * 100);
	rules.isdone = 0;
	rules.done_mutex = donemutex;
	rules.death_clock = (time_t)ft_atoi(av[2]);
	rules.eat_clock = (time_t)ft_atoi(av[3]);
	rules.sleep_clock = (time_t)ft_atoi(av[4]);
	if (ac == 6)
		rules.meal_nbr = ft_atoi(av[5]);
	else
		rules.meal_nbr = -1;
	return (rules);
}

t_philo	*init_philo(t_args rules, pthread_mutex_t *fork_array)
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
		philo_array[i].started = 0;
		philo_array[i].forks = fork_array;
		philo_array[i].printf_mutex = rules.print_mutex;
		philo_array[i].meals_eaten = 0;
		i++;
	}
	usleep(100);
	return (philo_array);
}
