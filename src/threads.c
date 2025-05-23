/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:52:35 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/23 19:09:26 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		*rout(void *arg);
static void	start_routine(t_philo *philo);
int			check_meals(t_ph *ph);

void	*monitor(void *arg)
{
	t_ph	*ph;
	int		i;

	ph = (t_ph *)arg;
	while (!death(ph, -1) && !check_meals(ph))
	{
		i = 0;
		while (i < ph->ph_cnt)
		{
			if ((ft_get_time() - last_meal(&ph->philo[i], -1)) > ph->t_die)
			{
				death(ph, 1);
				ft_print (&ph->philo[i], "died");
				break ;
			}
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

void	*rout(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	start_routine(philo);
	while (!death(philo->ph, -1) && !check_meals(philo->ph))
	{
		eating(philo); 
		if (!death(philo->ph, -1) && !check_meals(philo->ph))
			sleeping(philo);
		if (!death(philo->ph, -1) && !check_meals(philo->ph))
			thinking(philo);
	}
	return (NULL);
}

static void start_routine(t_philo *philo)
{
	if (philo->ph->ph_cnt == 1)
		return ;
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

int	check_meals(t_ph *ph)
{
	int	i;

	i = 0;
	if (ph->max_meals != -1)
	{
		while (i < ph->ph_cnt)
		{
			if (meals(&ph->philo[i], -1) < ph->max_meals)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
