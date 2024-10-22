/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:44:56 by nlambert          #+#    #+#             */
/*   Updated: 2024/10/22 16:52:51 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int rules(t_data *data, char **argv, int argc)
{
	t_rules rules;
	int i;

	i = 0;

	rules.nb_of_philosophers = ft_atoi(argv[1]);
	rules.time_to_die = ft_atoi(argv[2]);
	rules.time_to_eat = ft_atoi(argv[3]);
	rules.time_to_sleep = ft_atoi(argv[4]);
	rules.time_to_think = (rules.time_to_die - rules.time_to_eat \
							- rules.time_to_sleep) * 0.75;
	rules.time_must_eat = -1;
	if (argc == 6)
		rules.time_must_eat = ft_atoi(argv[5]);
	data->global_rules = rules;
	if (rules_parsing(&rules) == 1)
		return (-1);
	data->end = rules.nb_of_philosophers;

	/*malloc data chaque philo + mémoire pour toutes les data de la
	-> struct t_philo, pour un thread par philo et pour un mutex par fourchette*/

	/*Initialise le mutex pour écrire dans le terminal (write) et celui pour
	effectuer des vérifications pendant le programme (mutex check).
	Puis pour chaque nombre de philo on va créer un mutex par fourchette*/

	//return

}

int malloc_data(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->global_rules.nb_of_philosophers);
	if (!data->philo)
		return (0);
	//malloc le reste
}
