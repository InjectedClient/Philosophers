/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:29:28 by nlambert          #+#    #+#             */
/*   Updated: 2024/11/06 16:19:29 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	data.dead_philo = 0;
	if (argc < 5 || argc > 6)
		return (printf ("wrong number of arguments\n"));
	if (!check_arg(argc, argv))
		return (0);
	if (!rules_init(&data, argv))
		return (0);
	threads_init(&data);
	return (free_and_destroy(&data));
}
