/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:12:00 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/01 18:09:12 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include "struct.h" 

//	utils.c
int		ft_atoi(const char *nptr);
int		check_args(int ac, char **av);
time_t	actual_time(t_rules *rules);
time_t	get_time(void);

//	free.c
void	destroy_rules(t_rules *rules);
void	kill_ongoing_fork_array(t_fork *result, int i);
void	destroy_rules_2(t_rules *rules);
void	free_mutexes_philo(t_philo *table, int i, int stamp);

//	init_rules.c
t_rules	*init_rules(int ac, char **av);

//	init_philo.c
t_philo	*init_philos(t_rules *rules);

//	mutex_functions.c
void	grab_forks(t_philo	*philo);
void	drop_forks(t_philo	*philo);
void	actualise_meal_stamp(t_philo *philo);
void	printf_secured(time_t time, int id, char *str, t_rules *rules);
int		is_it_done(t_philo *philo);

//	mutex_functions_2.c
void	myusleep(int time, t_philo *philo);
void	update_meals(t_philo *philo);

//	routine.c
void *routine(void *args);

//	launchs.c
int	launch_philos(t_philo *table, t_rules *rules);
void	wait_philos(t_philo *table);

#endif