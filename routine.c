/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:55:43 by nlambert          #+#    #+#             */
/*   Updated: 2024/10/30 17:24:29 by nlambert         ###   ########.fr       */
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
	check si les deux fork peuvent etre lock
	lock/unlock + recup le temps avec get_time et le stock
	lock pour write les repas puis unlock
	usleep pour simuler le temps passer a manger[argv3], puis unlock
	decremente le nombre de repas a manger, si 0 decrementer end(nb de philo)
	unlock les deux fork pour les autres philo apres
*/
void	eating(t_philo *philo, int fork_1, int fork_2)
{
	if (!pthread_mutex_lock(&philo->data->forks[fork_1])
		&& !pthread_mutex_lock(&philo->data->forks[fork_2]))
	{
		pthread_mutex_lock(&philo->time_time);
		philo->time_time = get_time(philo->data->time);
		pthread_mutex_unlock(&philo->time_time);
		pthread_mutex_lock(&philo->data->write);
		print_meal(philo);
		pthread_mutex_unlock(&philo->data->write);
		ft_usleep(philo->data, philo->rules.time_to_eat);
		pthread_mutex_lock(&philo->data->mutex_check);
		philo->rules.time_must_eat --;
		if (philo->rules.time_must_eat == 0)
			philo->data->end --;
		pthread_mutex_unlock(&philo->data->mutex_check);
	}
	pthread_mutex_unlock(&philo->data->forks[fork_1]);
	pthread_mutex_unlock(&philo->data->forks[fork_2]);
}
/*
	check si != 1 philo
	definit la position des fork selon philo paire ou impaire
	(une des fork du dernier philo sera a indince 0) >>
	si un philosophe a l'ID 5 et qu'il y a 5 philosophes, 5 % 5 donne 0, bouclant ainsi le cercle.
	Chaque philosophe doit prendre la fourchette à sa gauche et à sa droite.
	En utilisant philo->id % philo->rules.nbr_philo, on s'assure que les indices des fourchettes sont correctement
	assignés même lorsque l'ID du philosophe est le dernier dans la séquence.
	eating est appele avec le philo et deux fork
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
	eating(philo, fork_1, fork_2);
}

/*
	si philo paire ou impaire -> soit mange soit penser
	infinite loop -> manger, dormir puis penser
*/
void	*routine(void *perso)
{
	t_philo *philo;

	philo = (t_philo *) perso;
	print_routine(philo);
	while (1)
	{
		forks_init(philo);
			print_action_and_wait(philo, "%ld %d" " is sleeping\n", philo->rules.time_to_sleep);
			print_action_and_wait(philo, "%ld %d" " is thinking\n", philo->rules.time_to_think);
		if (check_end(philo->data, philo) == 0)
			return ((void *) 0);
	}
}
