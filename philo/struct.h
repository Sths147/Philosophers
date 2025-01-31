/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:59:59 by sithomas          #+#    #+#             */
/*   Updated: 2025/01/31 15:43:44 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct	s_args
{
	size_t	nbr;
	size_t	death_clock;
	size_t	eat_clock;
	size_t	sleep_clock;
	size_t	meal_nbr;
}				t_args;

typedef struct	s_fork
{
	size_t			fork_id;
	pthread_mutex_t	mutex;
}				t_fork;


#endif