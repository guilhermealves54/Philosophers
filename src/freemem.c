/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:46:52 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/08 02:05:27 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_mem(t_ph *ph, int opt, int exit)
{
	int	i;

	i = 0;
	if (opt & 4)
	{
		while (i < ph->ph_cnt)
			pthread_mutex_destroy (&ph->forks[i++]);
		free(ph->forks);
	}
	if (opt & 2)
		free (ph->philo);
	if (opt & 1)
		pthread_mutex_destroy(&ph->print);
	return (exit);
}
