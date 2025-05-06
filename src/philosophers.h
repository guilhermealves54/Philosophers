/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:47 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/04 18:20:47 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//	Includes

# include <unistd.h>
# include <stdio.h>
# include <limits.h>

// Main Struct
typedef struct s_phil
{
	int	phil;
	int	forks;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	must_eat;
}	t_phil;

//	Funcs

// Initialization
int	init_phil(t_phil *phil, char **argv);

#endif
