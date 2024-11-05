/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:05:21 by nlambert          #+#    #+#             */
/*   Updated: 2024/11/05 16:51:23 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	est appelée qd un philo meurt
	udpate check et write qu'il est mort
*/
void	print_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->mutex_check);
	data->dead_philo = 1;
	pthread_mutex_unlock(&data->mutex_check);
	pthread_mutex_lock(&data->write);
	printf("%ld %d died\n", get_time(data->time), i);
	pthread_mutex_unlock(&data->write);
}

/*
	calcule le temps ecoule depuis le dernier repas du philo
	si temps ecoule depuis dernier repas > temps max sans manger
	-> le philo est considere mort
	utilise % pour revenir au 1er philo quand on est au dernier
*/
void	check_philo_life(t_data *data)
{
	int i;
	int time_last_meal;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex_check);
		time_last_meal = get_time(data->time) - data->philo[i].time_time;
		pthread_mutex_unlock(&data->mutex_check);
		if (time_last_meal > data->global_rules.time_to_die)
			return (print_death(data, i + 1));
		pthread_mutex_lock(&data->mutex_check);
		if (data->end == 0)
		{
			pthread_mutex_unlock(&data->mutex_check);
			return ;
		}
		pthread_mutex_unlock(&data->mutex_check);
		i ++;
		i = i % data->global_rules.nb_of_philosophers;
	}
}

/*
	check si on peut continuer donc que
	aucun philo est mort de faim ou si c'est la fin de la simulation (end = 0 donc plus de philo)
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
	check si le philo est dead avant de miam miam
	inclut le temps actuel + ID du philo
*/
void	print_meal(t_philo *philo)
{
	if (!check_end(philo->data, philo))
	{
			printf("%ld %d has taken fork1\n", philo->time_time, philo->id);
			printf("%ld %d has taken fork2\n", philo->time_time, philo->id);
			printf("%ld %d is eating\n", philo->time_time, philo->id);
	}
}

/*
	Sert a ecrire les actions des philos
	mutex WRITE pour pas que tout les philos write en mm temps
*/
void	print_action_and_wait(t_philo *philo, char *action, int time_action)
{
	pthread_mutex_lock(&philo->data->write);
	if (!check_end(philo->data, philo)
		&& philo->rules.nb_of_philosophers > 1)
	{
		printf(action, get_time(philo->data->time), philo->id);
	}
	pthread_mutex_unlock(&philo->data->write);
	ft_usleep(philo->data ,time_action);
}


