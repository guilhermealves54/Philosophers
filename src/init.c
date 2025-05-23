/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:30:20 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/23 18:32:23 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	valid_args(t_ph *ph);
static int	ft_strisdigit(const char *str);
static int	ft_atoi(const char *str);

int	init_phil(t_ph *ph, char **argv)
{
	ph->start_t = ft_get_time();
	ph->ph_cnt = ft_atoi(argv[1]);
	ph->frk_cnt = ph->ph_cnt;
	ph->t_die = ft_atoi(argv[2]);
	ph->t_eat = ft_atoi(argv[3]);
	ph->t_sleep = ft_atoi(argv[4]);
	ph->philo_died = 0;
	if (argv[5])
		ph->max_meals = ft_atoi(argv[5]);
	else
		ph->max_meals = -1;
	if (!valid_args(ph))
		return (0);
	pthread_mutex_init(&ph->print, NULL);
	pthread_mutex_init(&ph->philo_died_m, NULL);
	return (1);
}

static int	valid_args(t_ph *ph)
{
	if (ph->ph_cnt == -2 || ph->t_die == -2 || ph->t_eat == -2
		|| ph->t_sleep == -2 || ph->max_meals == -2)
		return (write(2, "Invalid Argument(s).\n", 21), 0);
	if (ph->ph_cnt == -3 || ph->t_die == -3 || ph->t_eat == -3
		|| ph->t_sleep == -3 || ph->max_meals == -3)
		return (write(2, "Arguments must be positive.\n", 28), 0);
	if (ph->ph_cnt == -4 || ph->t_die == -4 || ph->t_eat == -4
		|| ph->t_sleep == -4 || ph->max_meals == -4)
		return (write(2, "Arguments must be integers.\n", 28), 0);
	if (ph->ph_cnt < 1)
		return (write(2, "Need at least one philosopher.\n", 31), 0);
	if (ph->t_die == 0 || ph->t_eat == 0 || ph->t_sleep == 0)
		return (write(2, "0 milliseconds is invalid.\n", 27), 0);
	if (ph->max_meals == 0)
		return (write(2, "If \"number of times each philosopher must eat\" "
				"is specified, it needs to be more than 0.\n", 89), 0);
	return (1);
}

static int	ft_strisdigit(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (str[i] != '-' && str[i] != '+')
				return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_atoi(const char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	if (!ft_strisdigit (str))
		return (-2);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-3);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > INT_MAX)
			return (-4);
		i++;
	}
	return (res);
}
