/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:16:38 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/21 02:08:14 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		eating(t_philo *philo);
static void	grab_forks(t_philo *philo);
static void	rel_fork(t_philo *philo);
void		sleeping(t_philo *philo);

void	thinking(t_philo *philo)
{
	ft_print(philo, "is thinking");
}

void	eating(t_philo *philo)
{
	while (!philo_dead(philo->ph) && !check_meals(philo->ph))
	{
		if (time_to_eat(philo))
		{
			grab_forks(philo);
			pthread_mutex_lock(&philo->ph->verif);
			philo->last_meal = ft_get_time();
			philo->meals += 1;
			ft_print(philo, "is eating");
			if (philo->ph->max_eat != -1 && philo->meals == philo->ph->max_eat)
			{
				philo->ph->ate_enough += 1;
				if (philo->ph->ate_enough == philo->ph->ph_cnt)
				{
					philo->ph->print_allowed = 0;
					philo->ph->philo_died = 1;
				}
			}
			pthread_mutex_unlock(&philo->ph->verif);
			usleep(philo->ph->t_eat * 1000);
			rel_fork(philo);
			break ;
		}
		usleep(500);
	}
}

static void	grab_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		philo->grabd_r_frk = 1;
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		philo->grabd_l_frk = 1;
		ft_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		philo->grabd_l_frk = 1;
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		philo->grabd_r_frk = 1;
		ft_print(philo, "has taken a fork");
	}
}

static void	rel_fork(t_philo *philo)
{
	if (philo->grabd_l_frk)
		pthread_mutex_unlock(philo->left_fork);
	philo->grabd_l_frk = 0;
	if (philo->grabd_r_frk)
		pthread_mutex_unlock(philo->right_fork);
	philo->grabd_r_frk = 0;
}

void	sleeping(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	usleep(philo->ph->t_sleep * 1000);
}
