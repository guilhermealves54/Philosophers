/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:46:52 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/07 01:49:53 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_mem(t_ph *ph, int opt, int exit)
{
	int	i;

	i = 0;
	if (opt & 2)
	{
		while (i < ph->ph_cnt)
			pthread_mutex_destroy (&ph->forks[i++]);
		free(ph->forks);
	}
	if (opt & 1)
		free (ph->philo);
	return (exit);
}
