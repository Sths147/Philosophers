/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:22:21 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/31 18:31:14 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void	myusleep(int time, t_philo *philo)
{
	time_t	start;

	start = get_time();
	while (get_time() < start + time && philo->args->isdone == 0)
		usleep(100);
}

int		isdone(t_args	arg)
{
	pthread_mutex_lock(arg.done_mutex);
	if (arg.isdone == 1)
	{	
		pthread_mutex_unlock(arg.done_mutex);
		return (1);
	}
	pthread_mutex_unlock(arg.done_mutex);
	return (0);
}
