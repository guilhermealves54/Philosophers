/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:16:38 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/08 16:15:56 by gribeiro         ###   ########.fr       */
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

void	eating(t_philo *philo)
{
	philo->last_meal = ft_get_time();
	ft_print(philo, "is eating");
	usleep(philo->ph->t_eat * 1000);
	philo->meals += 1;
}

void	rel_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	philo->grabd_r_frk = 0;
	pthread_mutex_unlock(philo->right_fork);
	philo->grabd_l_frk = 1;
}

void	sleeping(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	usleep(philo->ph->t_sleep * 1000);
}
