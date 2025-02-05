/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:59:59 by sithomas          #+#    #+#             */
/*   Updated: 2025/02/05 14:26:23 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct	s_args
{
	int		nbr;
	time_t		death_clock;
	time_t	eat_clock;
	time_t		sleep_clock;
	int		meal_nbr;
	time_t	beg_time;
}				t_args;

typedef struct	s_fork
{
	size_t			fork_id;
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct	s_philo
{
	pthread_t	thread_id;
	int			philo_nbr;
	t_args		args;
	t_fork		fork;
	time_t		last_meal_stamp;
	time_t		last_sleep_stamp;
	_Bool		eats;
	_Bool		sleeps;
	_Bool		thinks;
	_Bool		is_dead;
}				t_philo;

#endif