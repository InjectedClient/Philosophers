/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:55:43 by nlambert          #+#    #+#             */
/*   Updated: 2024/11/07 12:25:32 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		print_wait(philo, "%ld %d is thinking\n", philo->rules.time_to_think);
	else if (philo->id == philo->rules.nb_philo)
		print_wait(philo, "%ld %d is thinking\n", philo->rules.time_to_eat);
}

void	eating(t_philo *philo, int fork_1, int fork_2)
{
	if (!pthread_mutex_lock(&philo->data->forks[fork_1])
		&& !pthread_mutex_lock(&philo->data->forks[fork_2]))
	{
		pthread_mutex_lock(&philo->data->mutex_check);
		philo->time_time = get_time(philo->data->time);
		pthread_mutex_unlock(&philo->data->mutex_check);
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

void	forks_init(t_philo *philo)
{
	int	fork_1;
	int	fork_2;

	fork_1 = 0;
	fork_2 = 0;
	if (philo->rules.nb_philo == 1)
		return ;
	if (philo->id % 2 == 0)
	{
		fork_1 = philo->id - 1;
		fork_2 = philo->id % philo->rules.nb_philo;
	}
	else if (philo->id % 2 != 0)
	{
		fork_1 = philo->id % philo->rules.nb_philo;
		fork_2 = philo->id - 1;
	}
	eating(philo, fork_1, fork_2);
}

void	*routine(void *perso)
{
	t_philo	*philo;

	philo = (t_philo *) perso;
	print_routine(philo);
	while (1)
	{
		forks_init(philo);
		print_wait(philo, "%ld %d" " is sleeping\n", philo->rules.time_to_sleep);
		print_wait(philo, "%ld %d" " is thinking\n", philo->rules.time_to_think);
		if (!check_end(philo->data, philo))
			return ((void *) 0);
	}
}
