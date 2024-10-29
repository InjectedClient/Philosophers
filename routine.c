/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:55:43 by nlambert          #+#    #+#             */
/*   Updated: 2024/10/29 17:29:31 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		print_action_and_wait(philo, "%ld %d is thinking\n", philo->rules.time_to_think);
	else if (philo->id == philo->rules.nb_of_philosophers)
		print_action_and_wait(philo, "%ld %d is thinking\n", philo->rules.time_to_eat);
}
/*
	Si le philoles deux fork en main, on le fait manger en
	actualisant l'heure de son dernier repas, en écrivant qu'il a pris ses
	fork et qu'il mange. On actualise le nombre de repas et
	on libère les mutexs des fork.
*/
void	eating(t_philo *philo, int fork_1, int fork_2)
{
	//faire eating
}
/*
	check si != 1 philo
	definit la position des fork selon philo paire ou impaire
	donc les philo sont a une table ronde
	(une des fork du dernier philo sera a indince 0)
*/
void	fork_init(t_philo *philo)
{
	int fork_1;
	int fork_2;

	fork_1 = 0;
	fork_2 = 0;
	if	(philo->rules.nb_of_philosophers == 1)
		return ;
	if (philo->rules.nb_of_philosophers % 2 == 0)
	{
		fork_1 = philo->id - 1;
		fork_2 = philo->id % philo->rules.nb_of_philosophers;
	}
	else if (philo->id % 2 != 0)
	{
		fork_1 = philo->id % philo->rules.nb_of_philosophers;
		fork_2 = philo->id - 1;
	}
	//finir -> eating(philo, fork_1, fork_2);
}

/*
	si philo paire ou impaire -> soit mange soit penser
	infinite loop -> manger, dormir puis penser
*/
void *routine(void *perso)
{
	t_philo *philo;

	philo = (t_philo *) perso;
	print_routine(philo);
	while (1)
	{
		forks_init(philo);
			//finir eating
	}
}
