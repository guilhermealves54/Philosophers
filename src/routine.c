/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:16:38 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/24 02:37:38 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philo *philo);

void	thinking(t_philo *philo)
{
	ft_print(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	usleep(philo->ph->t_sleep * 1000);
}
