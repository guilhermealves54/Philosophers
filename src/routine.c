/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:16:38 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/23 00:22:18 by gribeiro         ###   ########.fr       */
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

static int	checkfork(t_fork *fork)
{
	int	success;

	success = 0;
	pthread_mutex_lock(&fork->mutex);
	if (fork->taken == 0)
	{
		fork->taken = 1;
		success = 1;
	}
	pthread_mutex_unlock(&fork->mutex);
	return (success);
}

static void releasefork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->taken = 0;
	pthread_mutex_unlock(&fork->mutex);
}

static void fork_loop(t_philo *philo, t_fork *first, t_fork *secnd, int grdfrks)
{
	int	printed;

	printed = 0;
	while (!grdfrks && !philo_dead(philo->ph)
			&& !check_meals(philo->ph))
	{
		if (checkfork(first))
		{
			if (printed == 0)
				ft_print(philo, "has taken a fork");
			printed = 1;
			if (checkfork(secnd))
			{
				ft_print(philo, "has taken a fork");
				grdfrks = 1;
			}
			else
				releasefork (first);
		}	
	}
}

static void	grab_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		fork_loop (philo, philo->right_fork, philo->left_fork, 0);
	else
		fork_loop (philo, philo->left_fork, philo->right_fork, 0);
}

static void	rel_fork(t_philo *philo)
{
	releasefork (philo->right_fork);
	releasefork (philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	usleep(philo->ph->t_sleep * 1000);
}
