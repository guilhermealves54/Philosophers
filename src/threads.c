/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:52:35 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/21 02:44:28 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		*rout(void *arg);
static void	start_routine(t_philo *philo);
int			philo_dead(t_ph *ph);
int			check_meals(t_ph *ph);

void	*monitor(void *arg)
{
	t_ph	*ph;
	int		i;

	ph = (t_ph *)arg;
	while (!ph->ready_strt)
		usleep(100);
	while (!philo_dead(ph) && !check_meals(ph))
	{
		i = 0;
		while (i < ph->ph_cnt)
		{
			pthread_mutex_lock(&ph->verif);
			if ((ft_get_time() - ph->philo[i].last_meal) > ph->t_die)
			{
				ph->philo_died = 1;
				pthread_mutex_unlock(&ph->verif);
				ft_print (&ph->philo[i], "died");
				break ;
			}
			pthread_mutex_unlock(&ph->verif);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*rout(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->ph->ready_strt)
		usleep(100);
	start_routine(philo);
	while (!philo_dead(philo->ph) && !check_meals(philo->ph))
	{
		eating(philo); 
		if (!philo_dead(philo->ph) && !check_meals(philo->ph))
			sleeping(philo);
		if (!philo_dead(philo->ph) && !check_meals(philo->ph))
			thinking(philo);
	}
	return (NULL);
}

static void start_routine(t_philo *philo)
{
	if (philo->ph->ph_cnt % 2 != 0)
	{
		if (philo->id % 2 != 0)
			return ;
		else
		{
			thinking(philo);
			if (philo->id == philo->ph->ph_cnt - 1)
				usleep(philo->ph->t_sleep * 1000);
			else
				usleep(2 * philo->ph->t_sleep * 1000);
		}
	}
	else
	{
		if (philo->id % 2 != 0)
			return ;
		else
		{
			thinking(philo);
			usleep(philo->ph->t_sleep * 1000);
		}
	}
}

int	philo_dead(t_ph *ph)
{
	pthread_mutex_lock(&ph->verif);
	if (ph->philo_died)
	{
		pthread_mutex_unlock(&ph->verif);
		return (1);
	}
	pthread_mutex_unlock(&ph->verif);
	return (0);
}

int	check_meals(t_ph *ph)
{
	pthread_mutex_lock(&ph->verif);
	if (ph->ate_enough >= ph->ph_cnt)
	{
		ph->print_allowed = 0;
		pthread_mutex_unlock(&ph->verif);
		return (1);
	}
	pthread_mutex_unlock(&ph->verif);
	return (0);
}
