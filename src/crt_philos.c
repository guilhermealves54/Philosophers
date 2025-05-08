/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crt_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:44:15 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/08 16:23:53 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	philo_init(t_ph *ph);
static void	*ph_routine(void *arg);
static void	*monitor(void *arg);
static int	check_meals(t_ph *ph, int i);

int	create_philos(t_ph *ph)
{
	int	i;

	ph->philo = malloc (ph->ph_cnt * sizeof(t_philo));
	if (!ph->philo)
		return (write (2, "Malloc Error\n", 13), free_mem(ph, FREE_BASIC, 0));
	ph->forks = malloc (ph->ph_cnt * sizeof(pthread_mutex_t));
	if (!ph->philo)
		return (write (2, "Malloc Error\n", 13), free_mem(ph, FREE_BASIC
				| FREE_PHILO, 0));
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
		ph->philo[i].grabd_l_frk = 0;
		ph->philo[i].grabd_r_frk = 0;
		ph->philo[i].ph = ph;
		pthread_create(&ph->philo[i].thread, NULL, ph_routine, &ph->philo[i]);
		i++;
	}
	pthread_create(&ph->monitor, NULL, monitor, ph);
	return (1);
}

static void	*ph_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->ph->philo_died)
	{
		thinking(philo);
		if (philo->ph->philo_died)
			break ;
		grab_forks(philo);
		if (philo->ph->philo_died)
			break ;
		eating(philo);
		if (philo->ph->philo_died)
			break ;
		rel_fork(philo);
		if (philo->ph->philo_died)
			break ;
		sleeping(philo);
	}
	return (NULL);
}

static void	*monitor(void *arg)
{
	t_ph	*ph;
	int		i;

	ph = (t_ph *)arg;
	while (!ph->philo_died)
	{
		i = 0;
		while (i < ph->ph_cnt)
		{
			if ((ft_get_time() - ph->philo[i].last_meal) > ph->t_die)
			{
				ph->philo_died = 1;
				ft_print (ph->philo, "died");
				break ;
			}
			if (check_meals(ph, i))
				break ;
			i++;
		}
		usleep(1000);
	}
	unlock_rmain_frks(ph);
	return (NULL);
}

static int	check_meals(t_ph *ph, int i)
{
	if (ph->must_eat != -1 && ph->philo[i].meals == ph->must_eat)
	{
		ph->philo_died = 1;
		ft_print (ph->philo, "ate it's last meal");
		return (1);
	}
	return (0);
}
