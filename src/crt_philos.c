/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crt_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:44:15 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/23 19:10:05 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_forks(t_ph *ph);
static int	philo_init(t_ph *ph);
static int	philo_init_threads(t_ph *ph);

int	create_philos(t_ph *ph)
{
	ph->philo = malloc (ph->ph_cnt * sizeof(t_philo));
	if (!ph->philo)
		return (write (2, "Malloc Error\n", 13), free_mem(ph, FREE_BASIC, 0));
	ph->forks = malloc (ph->ph_cnt * sizeof(t_fork));
	if (!ph->forks)
		return (write (2, "Malloc Error\n", 13), free_mem(ph, FREE_BASIC
				| FREE_PHILO, 0));
	init_forks(ph);
	if (!philo_init(ph))
		return (write (2, "Error creating thread\n", 23),
			free_mem(ph, FREE_BASIC | FREE_PHILO | DSTROY_FRK, 0));
	return (1);
}

static void	init_forks(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->ph_cnt)
	{
		ph->forks[i].taken = 0;
		pthread_mutex_init (&ph->forks[i].mutex, NULL);
		i++;
	}
}

static int	philo_init(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->ph_cnt)
	{
		ph->philo[i].id = i;
		ph->philo[i].meals = 0;
		pthread_mutex_init (&ph->philo[i].meals_m, NULL);
		ph->philo[i].last_meal = ft_get_time();
		pthread_mutex_init (&ph->philo[i].last_meal_m, NULL);
		ph->philo[i].left_fork = &ph->forks[i];
		ph->philo[i].right_fork = &ph->forks[(i + 1) % ph->ph_cnt];
		ph->philo[i].ph = ph;

		i++;
	}
	if (!philo_init_threads(ph))
		return(0);
	return (1);
}

static int	philo_init_threads(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->ph_cnt)
	{
		if (pthread_create(&ph->philo[i].th, NULL, rout, &ph->philo[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(ph->philo[i].th, NULL);
			return (0);
		}
		i++;
	}
	if (pthread_create(&ph->monitor, NULL, monitor, ph) != 0)
	{
		while (--i >= 0)
			pthread_join(ph->philo[i].th, NULL);
		return (0);
	}
	return (1);
}
