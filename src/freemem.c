/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:46:52 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/23 00:23:29 by gribeiro         ###   ########.fr       */
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
			pthread_mutex_destroy (&ph->forks[i++].mutex);
		free(ph->forks);
	}
	if (opt & 2)
		free (ph->philo);
	if (opt & 1)
	{
		pthread_mutex_destroy(&ph->print);
		pthread_mutex_destroy(&ph->verif);
	}
	return (exit);
}
