/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:49:36 by nlambert          #+#    #+#             */
/*   Updated: 2024/11/07 14:42:44 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((str[i] >= '\t' && str[i] <= '\r')
		|| str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if ((sign * nb) < INT_MIN || (sign * nb) > INT_MAX)
		return (-1);
	return ((int)sign * nb);
}

void	free_all(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->thread_id)
		free(data->thread_id);
	if (data->forks)
		free(data->forks);
}

int	free_and_destroy(t_data *data)
{
	int	i;
	int	mutex;

	mutex = 0;
	i = 0;
	while (i < data->global_rules.nb_philo)
	{
		if (pthread_mutex_destroy(&data->forks[i]))
			mutex ++;
		i ++;
	}
	if (pthread_mutex_destroy(&data->mutex_check))
		mutex ++;
	if (pthread_mutex_destroy(&data->write))
		mutex ++;
	if (data->forks)
		free(data->forks);
	if (data->thread_id)
		free(data->thread_id);
	if (data->philo)
		free(data->philo);
	return (mutex);
}

long	get_time(long t)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000 - t);
}

void	ft_usleep(t_data *data, long time_action)
{
	long	start_t;
	long	cur_t;

	start_t = get_time(0);
	cur_t = start_t;
	while (check_end(data, &data->philo[0])
		&& (cur_t - start_t) < time_action)
	{
		usleep(100);
		cur_t = get_time(0);
	}
}
