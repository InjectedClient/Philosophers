/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:20:40 by nlambert          #+#    #+#             */
/*   Updated: 2024/11/07 14:13:23 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arg(int argc, char **argv)
{
	int	i;
	int	arg;
	int	count_num_len;

	arg = 1;
	while (arg <= (argc - 1))
	{
		i = 0;
		count_num_len = 0;
		if (argv[arg][i] == '-' || argv[arg][i] == '+')
			i ++;
		while (argv[arg][i])
		{
			if (!(argv[arg][i] >= '0' && argv[arg][i] <= '9'))
				return (printf("arguments should be numbers only\n"), 0);
			count_num_len += argv[arg][i] != 0;
			i ++;
		}
		if (count_num_len > 10)
			return (printf("argument too long > 10 digits\n"), 0);
		arg ++;
	}
	return (1);
}

int	check_arg2(t_rules *rules)
{
	if (rules->nb_philo <= 0 || rules->time_to_die <= 0 || \
		rules->time_to_eat <= 0 || rules->time_to_sleep <= 0)
	{
		printf("Wrong arguments !\n");
		return (0);
	}
	return (1);
}
