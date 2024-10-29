/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:49:36 by nlambert          #+#    #+#             */
/*   Updated: 2024/10/29 16:29:42 by nlambert         ###   ########.fr       */
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
	if (data->thread_ids)
		free(data->thread_ids);
	if (data->forks)
		free(data->forks);
}
/*
	accede a l'heure
*/
long	get_time(long t)
{
	struct	timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000 - t);
}
/*
	mets un thread en pause et check si le prog peut continuer
*/
void	ft_usleep(t_data *data, long time_action)
{
	long	start_t;
	long	cur_t;

	start_t = get_time(0);
	cur_t = start_t;
	while (check_end(data, &data->philo[0]) != -1 && (cur_t - start_t) < time_action)
	{
		usleep(100);
		cur_t = get_time(0);
	}
}
