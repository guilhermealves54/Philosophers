/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:04:28 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/24 02:32:02 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	last_meal(t_philo *philo, long timecode);
int		meals(t_philo *philo, int status);
int		checkfork(t_fork *fork);
void	releasefork(t_fork *fork);

int	death(t_ph *ph, int status)
{
	int	value;

	pthread_mutex_lock(&ph->philo_died_m);
	if (status != -1)
	{
		ph->philo_died = status;
		value = status;
	}
	else
		value = ph->philo_died;
	pthread_mutex_unlock(&ph->philo_died_m);
	return (value);
}

long	last_meal(t_philo *philo, long timecode)
{
	long	value;

	pthread_mutex_lock(&philo->last_meal_m);
	if (timecode != -1)
	{
		philo->last_meal = timecode;
		value = timecode;
	}
	else
		value = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_m);
	return (value);
}

int	meals(t_philo *philo, int status)
{
	int	value;

	pthread_mutex_lock(&philo->meals_m);
	if (status != -1)
	{
		philo->meals += status;
		value = philo->meals;
	}
	else
		value = philo->meals;
	pthread_mutex_unlock(&philo->meals_m);
	return (value);
}

int	checkfork(t_fork *fork)
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

void	releasefork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->taken = 0;
	pthread_mutex_unlock(&fork->mutex);
}
