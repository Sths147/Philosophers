/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:48:44 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/13 17:33:16 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <sys/time.h>
#include "struct.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

t_philo	*init_philo(t_args rules, pthread_mutex_t *fork_array);
time_t	actual_time(t_args rules);
void	check_time(t_philo *philo);
pthread_mutex_t	*init_forks(t_args rules);
t_args	init_rules(int ac, char **av);
size_t	atosize_t(const char *nptr);
int	ft_atoi(const char *nptr);
void *routine(void *args);

#endif