/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:48:44 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/31 16:20:46 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include "struct.h"

t_philo			*init_philo(t_args *rules, pthread_mutex_t *fork_array);
void			free_mutex(pthread_mutex_t	*forks, int nbr);
int				check_args(int ac, char **av);
void			myusleep(int time, t_philo *philo);
void			printf_secured(time_t time, int id, char *str, pthread_mutex_t *mutex);
time_t			actual_time(t_args *rules);
pthread_mutex_t	*init_forks(t_args *rules);
t_args			*init_rules(int ac, char **av);
size_t			atosize_t(const char *nptr);
int				ft_atoi(const char *nptr);
void			*routine(void *args);
time_t	get_time(void);
int		isdone(t_args	arg);

#endif