/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:44:56 by nlambert          #+#    #+#             */
/*   Updated: 2024/11/06 16:19:18 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	alloue memorie pour le nb de philo
	pour un thread par philo et un mutex par fork
*/
int	malloc_init(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->global_rules.nb_philo);
	if (!data->philo)
	{
		free (data->philo);
		printf("Allocation problem : philo\n");
		return (0);
	}
	data->thread_id = malloc(sizeof(pthread_t) * data->global_rules.nb_philo);
	if (!data->thread_id)
	{
		free (data->philo);
		free (data->thread_id);
		printf("Allocation problem : threads_id\n");
		return (0);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->global_rules.nb_philo);
	if (!data->forks)
	{
		free (data->forks);
		free (data->thread_id);
		free (data->philo);
		printf("Allocation problem : forks \n");
		return (0);
	}
	return (1);
}

/*
	initialise le mutex pour write dans le term
	et mutex check pour verif pendant le prog
	puis check nb philo et creer un mutex par fork
*/
int	mutex_init(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->mutex_check, NULL) != 0)
	{
		pthread_mutex_destroy(&data->write);
		return (0);
	}
	i = 0;
	while (i < data->global_rules.nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (i-- >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&data->write);
			pthread_mutex_destroy(&data->mutex_check);
			return (0);
		}
		i ++;
	}
	return (1);
}

/*
	assigne a chaque philo les donnes utiles
	pour le reste du prog
*/
void	philo_init(t_data *data, char **argv)
{
	int	i;

	i = 0;
	while (i < data->global_rules.nb_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].time_time = 0;
		data->philo[i].rules = data->global_rules;
		if (argv[5])
			data->philo[i].rules.time_must_eat = ft_atoi(argv[5]);
		else
			data->philo[i].rules.time_must_eat = -1;
		i++;
	}
}

/*
	assigne a chaque regle une valeure
	malloc chaque data a utiliser (nb pihlo, nb de fourchettes
	et le nombre de nombre de threads)
	initalise les mutex
*/
int	rules_init(t_data *data, char **argv)
{
	t_rules	rules;

	rules.nb_philo = ft_atoi(argv[1]);
	rules.time_to_die = ft_atoi(argv[2]);
	rules.time_to_eat = ft_atoi(argv[3]);
	rules.time_to_sleep = ft_atoi(argv[4]);
	rules.time_to_think = (rules.time_to_die - rules.time_to_eat \
							- rules.time_to_sleep) * 0.75;
	data->global_rules = rules;
	if (!check_arg2(&rules))
		return (0);
	data->end = rules.nb_philo;
	if (!malloc_init(data))
		return (0);
	if (!mutex_init(data))
		return (free_all(data), 0);
	return (philo_init(data, argv), 1);
}

/*
	initalise un thread par philo et execute routine
	create -> 1-(id de thread 2-NULL > attributs par defaut
	3- &routine > fonction qui va s'executer 4-pour passer
	des arg a la fonction)
	join -> attend la fin de tous les thread et retourne 1/2 si erreur

*/
int	threads_init(t_data *data)
{
	int	i;

	i = 0;
	data->time = get_time(0);
	while (i < data->global_rules.nb_philo)
	{
		if (pthread_create(&data->thread_id[i], \
				NULL, &routine, &data->philo[i]))
		{
			while (i -- >= 0)
				pthread_join(data->thread_id[i], NULL);
			return (printf("\033[31mProblem creating threads !\n\033[0m"), 0);
		}
		i ++;
	}
	check_philo_life(data);
	i = 0;
	while (i < data->global_rules.nb_philo)
	{
		if (pthread_join(data->thread_id[i], NULL))
			return (printf("\033[31mProblem ending threads !\n\033[0m"), 0);
		i ++;
	}
	return (0);
}
