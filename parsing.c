/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Barg: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:05:08 barg nlambert          #+#    #+#             */
/*   Updated: 2024/10/22 14:14:19 barg nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	parsing pour verif si les arg sont que des chiffres et pas > a 10  carac
*/
int check_arg(int argc, char **argv)
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
/*
	check le cas de 0
*/
int	rules_parsing(t_rules *rules)
{
	if (rules->nb_of_philosophers<= 0 || rules->time_to_die <= 0 || \
		rules->time_to_eat <= 0 || rules->time_to_sleep <= 0)
	{
		printf("Wrong arguments !\n");
		return (0);
	}
	return (1);
}
