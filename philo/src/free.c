/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:24:10 by sithomas          #+#    #+#             */
/*   Updated: 2025/03/20 16:30:11 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void	free_mutex(pthread_mutex_t	*forks, int nbr)
{
	int i;
	
	i = 0;
	while (i < nbr)
	{
		if (pthread_mutex_destroy(&forks[i]) == -1)
			return (perror("mutex destroy error"));
		i++;
	}
	free(forks);
}
