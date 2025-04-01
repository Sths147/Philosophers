/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:12:51 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/01 17:54:40 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_fork
{
	_Bool			is_taken;
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_rules
{
	int				nbr;
	int				meals_nbr;
	int				is_done;
	time_t			die_time;
	time_t			eat_time;
	time_t			sleep_time;
	time_t			beg_time;
	t_fork			*forks;
	pthread_mutex_t	mutex_printf;
	pthread_mutex_t	isdone_mutex;
}					t_rules;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				philo_id;
	_Bool			eats;
	_Bool			is_done;
	pthread_mutex_t	done_mutex;
	t_rules			*rules;
	t_fork			*left_fork;
	t_fork			*right_fork;
	time_t			last_meal_stamp;
	pthread_mutex_t	stamp_mutex;
	int				meals_eaten;
	pthread_mutex_t	meals_mutex;
}				t_philo;