/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:29:28 by nlambert          #+#    #+#             */
/*   Updated: 2024/10/24 14:51:24 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	t_data data;

	if (argc < 5 || argc > 6)
		return (printf ("wrong number of arguments\n"));
	if (!check_arg(argc, argv))
		return (0);
	if (!rules(&data, argv, argc))
		return (0);

}
