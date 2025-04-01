/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:11:00 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/01 18:39:22 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_rules	*rules;
	t_philo	*table;
	int		i;

	if (check_args(ac, av))
		return (printf("Wrong arguments :( Try again!"));
	rules = init_rules(ac, av);
	if (!rules)
	return (1);
	table = init_philos(rules);
	i = 0;
	while (i < rules->nbr - 1)
	{
		printf("fourchette droite du philo numéro %d, %p\n", table[i].philo_id, &table[i].left_fork->fork);
		printf("fourchette gauche du philo numéro %d, %p\n", table[i].philo_id, &table[i].right_fork->fork);
		i++;
	}
	if (!table)
	{
		destroy_rules_2(rules);
		return (1);
	}
	launch_philos(table, rules);
	wait_philos(table);
	return (0);
}
