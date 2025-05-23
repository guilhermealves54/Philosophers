/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:46:52 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/23 18:38:31 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_philo(t_ph *ph);

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
		free_philo(ph);
	if (opt & 1)
	{
		pthread_mutex_destroy(&ph->print);
		pthread_mutex_destroy(&ph->philo_died_m);
	}
	return (exit);
}

static void	free_philo(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->ph_cnt)
	{
		pthread_mutex_destroy (&ph->philo[i].meals_m);
		pthread_mutex_destroy (&ph->philo[i].last_meal_m);
		i++;
	}
	free (ph->philo);
}
