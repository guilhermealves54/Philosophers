/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crt_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:44:15 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/23 00:34:56 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	philo_init(t_ph *ph);

int	create_philos(t_ph *ph)
{
	int	i;

	ph->philo = malloc (ph->ph_cnt * sizeof(t_philo));
	if (!ph->philo)
		return (write (2, "Malloc Error\n", 13), free_mem(ph, FREE_BASIC, 0));
	ph->forks = malloc (ph->ph_cnt * sizeof(t_fork));
	if (!ph->forks)
		return (write (2, "Malloc Error\n", 13), free_mem(ph, FREE_BASIC
				| FREE_PHILO, 0));
	i = 0;
	while (i < ph->ph_cnt)
	{
		ph->forks[i].taken = 0;
		pthread_mutex_init (&ph->forks[i].mutex, NULL);
		i++;
	}
	pthread_mutex_lock(&ph->verif);
	if (!philo_init(ph))
		return (write (2, "Error creating thread\n", 23),
			free_mem(ph, FREE_BASIC | FREE_PHILO | DSTROY_FRK, 0));
	ph->ready_strt = 1;
	pthread_mutex_unlock(&ph->verif);
	return (1);
}

static int	philo_init(t_ph *ph)
{
	int	i;

	i = 0;
	if (pthread_create(&ph->monitor, NULL, monitor, ph) != 0)
		return (pthread_join(ph->monitor, NULL), 0);
	while (i < ph->ph_cnt)
	{
		ph->philo[i].id = i;
		ph->philo[i].meals = 0;
		ph->philo[i].last_meal = ft_get_time();
		ph->philo[i].left_fork = &ph->forks[i];
		ph->philo[i].right_fork = &ph->forks[(i + 1) % ph->ph_cnt];
		ph->philo[i].ph = ph;
		if (pthread_create(&ph->philo[i].th, NULL, rout, &ph->philo[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(ph->philo[i].th, NULL);
			return (0);
		}
		i++;
	}
	return (1);
}

