/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crt_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:44:15 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/07 01:55:24 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	philo_init(t_ph *ph);
static void	*ph_routine(void *arg);

int	create_philos(t_ph *ph)
{
	int	i;

	ph->philo = malloc (ph->ph_cnt * sizeof(t_philo));
	if (!ph->philo)
		return (write (2, "Malloc Error\n", 13), 0);
	ph->forks = malloc (ph->ph_cnt * sizeof(pthread_mutex_t));
	if (!ph->philo)
		return (write (2, "Malloc Error\n", 13), free_mem(ph, FREE_PHILO, 0));
	i = 0;
	while (i < ph->ph_cnt)
		pthread_mutex_init (&ph->forks[i++], NULL);
	if (!philo_init(ph))
		return (0);
	return (1);
}

static int	philo_init(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->ph_cnt)
	{
		ph->philo[i].id = i;
		ph->philo[i].meals = 0;
		ph->philo[i].last_meal = ft_get_time();
		ph->philo[i].left_fork = &ph->forks[i];
		ph->philo[i].right_fork = &ph->forks[(i + 1) % ph->ph_cnt];
		ph->philo[i].ph = ph;
		pthread_create(&ph->philo[i].thread, NULL, ph_routine, &ph->philo[i]);
	}
	return (1);
}

static void *ph_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (!philo->ph->philo_died)
    {
        // Think
        // Take forks
        // Eat
        // Release forks
        // Sleep
		printf ("Time since last meal: %ld\n", philo->last_meal);
		philo->ph->philo_died = 1;
    }
    return (NULL);
}
