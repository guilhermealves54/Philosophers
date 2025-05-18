/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:43:23 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/17 23:19:16 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print(t_philo *philo, char *msg);
void	unlock_rmain_frks(t_ph *ph);
int		allowed_to_eat(t_philo *philo);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

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

void	unlock_rmain_frks(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->ph_cnt)
	{
		if (ph->philo[i].grabd_l_frk)
			pthread_mutex_unlock(ph->philo[i].left_fork);
		if (ph->philo[i].grabd_r_frk)
			pthread_mutex_unlock(ph->philo[i].right_fork);
		i++;
	}
}

int	allowed_to_eat(t_philo *philo)
{
	if (ft_get_time() == philo->ph->start_t)
	{
		if (philo->ph->ph_cnt % 2 == 0 && philo->id % 2 == 0)
			return (1);
		if (philo->ph->ph_cnt % 2 != 0 && philo->id % 2 != 0)
			return (1);
		return (0);
	}
	return (1);
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
