/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:43:23 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/24 02:32:19 by gribeiro         ###   ########.fr       */
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
	if ((ft_strncmp(msg, "died", 4) == 0 || !death(philo->ph, -1))
		&& !check_meals(philo->ph))
		printf("%ld %d %s\n", tstamp, philo->id + 1, msg);
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
	if (meals(philo, -1) == 0)
		return (1);
	else
	{
		if (philo->ph->ph_cnt % 2 != 0)
		{
			if (ft_get_time() - last_meal(philo, -1) < (3 * philo->ph->t_eat))
				return (0);
		}
		else
		{
			if (ft_get_time() - last_meal(philo, -1) < (2 * philo->ph->t_eat))
				return (0);
		}
	}
	return (1);
}
