/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:16:38 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/20 17:09:06 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	grab_forks(t_philo *philo);
void	eating(t_philo *philo);
void	rel_fork(t_philo *philo);
void	sleeping(t_philo *philo);

void	thinking(t_philo *philo)
{
	ft_print(philo, "is thinking");
}

void	grab_forks(t_philo *philo)
{
	if (time_to_eat(philo))
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
}

void	eating(t_philo *philo)
{
	philo->last_meal = ft_get_time();
	pthread_mutex_lock(&philo->ph->verif);
	ft_print(philo, "is eating");
	philo->meals += 1;
	if (philo->ph->must_eat != -1 && philo->meals == philo->ph->must_eat)
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
}

void	rel_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	philo->grabd_r_frk = 0;
	pthread_mutex_unlock(philo->right_fork);
	philo->grabd_l_frk = 0;
}

void	sleeping(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	usleep(philo->ph->t_sleep * 1000);
}
