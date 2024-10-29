/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:50:31 by nlambert          #+#    #+#             */
/*   Updated: 2024/10/29 17:28:02 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#	define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <time.h>
# include <unistd.h>
# include <errno.h>
# include <sys/time.h>

typedef struct s_rules
{
	int	nb_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_think;
	int time_must_eat;
}	t_rules;

typedef struct s_philo
{
	t_rules			rules;
	struct s_data	*data;
	int				id;
	long			time_time;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	t_rules			global_rules;
	pthread_t		*thread_ids;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	mutex_check;
	int				end;
	long long		time;
	int				dead_philo;
}	t_data;

int		check_arg(int argc, char **argv);
int		main(int argc, char **argv);
int		ft_atoi(const char *str);
int		rules(t_data *data, char **argvc, int argc);
int		rules_parsing(t_rules *rules);
int		malloc_data(t_data *data);
int		mutex_init(t_data *data);
void	free_all(t_data *data);
int		mutex_init(t_data *data);
void	philo_init(t_data *data);
int		init_threads(t_data *data);
long	get_time(long t);
void 	*routine(void *perso);
void	print_routine(t_philo *philo);
void	print_action_and_wait(t_philo *philo, char *action, int time_action);
int		check_end(t_data *data, t_philo *philo);
void	ft_usleep(t_data *data, long time_action);
void	fork_init(t_philo *philo);

#	endif
