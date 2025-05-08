/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:43:23 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/08 16:19:55 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print(t_philo *philo, char *msg);
void	unlock_rmain_frks(t_ph *ph);

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
	printf("%ld %d %s\n", tstamp, philo->id + 1, msg);
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
