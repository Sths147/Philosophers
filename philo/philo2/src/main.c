/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:11:00 by sithomas          #+#    #+#             */
/*   Updated: 2025/04/03 10:47:49 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_rules	*rules;
	t_philo	*table;

	if (check_args(ac, av) || special_cases(av))
		return (1);
	rules = init_rules(ac, av);
	if (!rules)
		return (1);
	table = init_philos(rules);
	if (!table)
	{
		destroy_rules_2(rules);
		return (1);
	}
	if (launch_philos(table, rules))
		return (1);
	if (watch(table, rules))
		return (1);
	clean_all(table, rules);
	return (0);
}
