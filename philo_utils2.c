/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:05:21 by nlambert          #+#    #+#             */
/*   Updated: 2024/10/29 16:30:14 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	check si on peut continuer donc que
	aucun philo est mort de faim ou si c'est la fin de la simulation
*/
int	check_end(t_data *data, t_philo *philo)
{
	(void)philo;
	pthread_mutex_lock(&data->mutex_check);
	if (data->dead_philo || data->end == 0)
	{
		pthread_mutex_unlock(&data->mutex_check);
		return (0);
	}
	pthread_mutex_unlock(&data->mutex_check);
	return (1);
}

/*
	Sert a ecrire les actions des philos
	mutex WRITE pour pas que tout les philos write en mm temps
*/
void	print_action_and_wait(t_philo *philo, char *action, int time_action)
{
	pthread_mutex_lock(&philo->data->write);
	if (check_end(philo->data, philo) != 0 && philo->rules.nb_of_philosophers > 1)
	{
		printf(action, get_time(philo->data->time), philo->id);
	}
	pthread_mutex_unlock(&philo->data->write);
	ft_usleep(philo->data, time_action);
}