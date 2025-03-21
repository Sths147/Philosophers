/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:59:59 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/21 13:50:43 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_args
{
	int				nbr;
	pthread_mutex_t	*print_mutex;
	time_t			death_clock;
	time_t			eat_clock;
	time_t			sleep_clock;
	int				meal_nbr;
	time_t			beg_time;
	_Bool			isdone;
	pthread_mutex_t	*done_mutex;
}					t_args;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				philo_nbr;
	t_args			args;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*printf_mutex;
	time_t			last_meal_stamp;
	int				meals_eaten;
	_Bool			started;
	_Bool			eats;
	_Bool			sleeps;
	_Bool			thinks;
	_Bool			is_dead;
}					t_philo;

#endif