/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:16:38 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/23 19:50:46 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		eating(t_philo *philo);
static void fork_loop(t_philo *philo, t_fork *frst, t_fork *secnd, int grdfrks);
static void	grab_forks(t_philo *philo);
static void	rel_fork(t_philo *philo);
void		sleeping(t_philo *philo);

void	thinking(t_philo *philo)
{
	ft_print(philo, "is thinking");
}

void	eating(t_philo *philo)
{
	while (!death(philo->ph, -1) && !check_meals(philo->ph))
	{
		if (time_to_eat(philo))
		{
			grab_forks(philo);
			last_meal(philo, ft_get_time());
			ft_print(philo, "is eating");
			usleep(philo->ph->t_eat * 1000);
			meals (philo, 1);
			rel_fork(philo);
			break ;
		}
		usleep(500);
	}
}

static void fork_loop(t_philo *philo, t_fork *frst, t_fork *secnd, int grdfrks)
{
	int	printed;

	printed = 0;
	while (!grdfrks && !death(philo->ph, -1) && !check_meals(philo->ph))
	{
		if (checkfork(frst))
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
				releasefork (frst);
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
