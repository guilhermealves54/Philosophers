/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:43:23 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/21 02:14:23 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print(t_philo *philo, char *msg);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		time_to_eat(t_philo *philo);

long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_print(t_philo *philo, char *msg)
{
	long	tstamp;

	tstamp = ft_get_time() - philo->ph->start_t;
	pthread_mutex_lock(&philo->ph->print);
	if (philo->ph->print_allowed)
	{
		printf("%ld %d %s\n", tstamp, philo->id + 1, msg);
		if (ft_strncmp(msg, "died", 4) == 0)
			philo->ph->print_allowed = 0;
	}
	pthread_mutex_unlock(&philo->ph->print);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

int	time_to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->ph->verif);
	if (philo->meals == 0)
		return (pthread_mutex_unlock(&philo->ph->verif), 1);
	else
	{
		if (philo->ph->ph_cnt % 2 != 0)
		{
			if (ft_get_time() - philo->last_meal < (3 * philo->ph->t_eat))
				return (pthread_mutex_unlock(&philo->ph->verif), 0);
		}
		else
		{
			if (ft_get_time() - philo->last_meal < (2 * philo->ph->t_eat))
				return (pthread_mutex_unlock(&philo->ph->verif), 0);
		}
	}
	pthread_mutex_unlock(&philo->ph->verif);
	return (1);
}
