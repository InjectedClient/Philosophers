/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:05:21 by nlambert          #+#    #+#             */
/*   Updated: 2024/11/07 15:28:06 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->mutex_check);
	data->dead_philo = 1;
	pthread_mutex_unlock(&data->mutex_check);
	pthread_mutex_lock(&data->write);
	printf("%ld %d died\n", get_time(data->time), i);
	pthread_mutex_unlock(&data->write);
}

void	check_philo_life(t_data *data)
{
	int	i;
	int	time_last_meal;

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
		i = i % data->global_rules.nb_philo;
	}
}

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

void	print_meal(t_philo *philo)
{
	if (check_end(philo->data, philo))
	{
		printf("%ld %d has taken a fork\n", philo->time_time, philo->id);
		printf("%ld %d has taken a fork\n", philo->time_time, philo->id);
		printf("%ld %d is eating\n", philo->time_time, philo->id);
	}
}

void	print_wait(t_philo *philo, char *action, int time_action)
{
	pthread_mutex_lock(&philo->data->write);
	if (check_end(philo->data, philo)
		&& philo->rules.nb_philo > 1)
	{
		printf(action, get_time(philo->data->time), philo->id);
	}
	pthread_mutex_unlock(&philo->data->write);
	ft_usleep(philo->data, time_action);
}
