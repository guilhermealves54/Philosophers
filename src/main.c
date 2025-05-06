/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:31:19 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/06 17:49:42 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_phil(t_phil *phil, char **argv);
static int	valid_args(t_phil *phil);
static int	ft_atoi(const char *str);

int	main(int argc, char **argv)
{
	t_phil  phil;

	if (argc < 5 || argc > 6)
		return (write(2, "Invalid Argument(s).\n", 21), 1);
	if (!init_phil(&phil, argv))
		return (1);
	return (0);
}

static int	init_phil(t_phil *phil, char **argv)
{
	phil->phil = ft_atoi(argv[1]);
	phil->forks = phil->phil;
	phil->t_die = ft_atoi(argv[2]);
	phil->t_eat = ft_atoi(argv[3]);
	phil->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		phil->must_eat = ft_atoi(argv[5]);
	else
		phil->must_eat = -1;
	if (!valid_args(phil))
		return (0);
	return (1);
}

static int	valid_args(t_phil *phil)
{
	if (phil->phil == -2 || phil->t_die == -2 || phil->t_eat == -2 
			|| phil->t_sleep == -2)
		return (write(2, "Invalid Argument(s).\n", 21), 0);
	if (phil->phil == -3 || phil->t_die == -3 || phil->t_eat == -3 
			|| phil->t_sleep == -3 || phil->must_eat == -3)
		return (write(2, "Arguments must be positive.\n", 28), 0);
	if (phil->phil == -4 || phil->t_die == -4 || phil->t_eat == -4 
			|| phil->t_sleep == -4 || phil->must_eat == -4)
		return (write(2, "Arguments must be integers.\n", 28), 0);
	if (phil->phil < 1)
		return (write(2, "Need at least one philosopher.\n", 31), 0);
	if (phil->t_die == 0 || phil->t_eat == 0 || phil->t_sleep == 0)
		return (write(2, "0 milliseconds is invalid.\n", 27), 0);
	if (phil->must_eat == 0)
		return (write(2, "If number of times each philosopher must eat "
				"is specified, it needs to be more then 0.\n", 87), 0);
	return (1);
}

static int	ft_atoi(const char *str)
{
	long res;
	int	i;

	res = 0;
	i = 0;
	if (!str)
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
