/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:47:32 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/21 02:21:17 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_ph	ph;
	int		i;

	if (argc < 5 || argc > 6)
		return (write(2, "Invalid Argument(s).\n", 21), 1);
	if (!init_phil(&ph, argv))
		return (1);
	if (!create_philos(&ph))
		return (1);
	i = 0;
	while (i < ph.ph_cnt)
		pthread_join(ph.philo[i++].th, NULL);
	pthread_join(ph.monitor, NULL);
	return (free_mem (&ph, FREE_BASIC | FREE_PHILO | DSTROY_FRK, 0));
}