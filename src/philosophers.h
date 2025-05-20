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

# define FREE_BASIC		1
# define FREE_PHILO		2
# define FREE_FORKS		4

//	INCLUDES

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

//	STRUCTS

// Philosophers Struct Array
typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				grabd_l_frk;
	int				grabd_r_frk;
	struct s_ph		*ph;
}	t_philo;

// Main Struct
typedef struct s_ph
{
	long			start_t;
	int				ph_cnt;
	int				frk_cnt;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				ate_enough;
	int				print_allowed;
	int				philo_died;
	pthread_t		monitor;
	pthread_mutex_t	verif;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_philo			*philo;
}	t_ph;

//	FUNCS

// Initialization
int		init_phil(t_ph *ph, char **argv);
int		create_philos(t_ph *ph);

// Routine
void	thinking(t_philo *philo);
void	grab_forks(t_philo *philo);
void	eating(t_philo *philo);
void	rel_fork(t_philo *philo);
void	sleeping(t_philo *philo);
int		allowed_to_eat(t_philo *philo);

// Utils
long	ft_get_time(void);
void	ft_print(t_philo *philo, char *msg);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// Memmory Cleanup
int		free_mem(t_ph *ph, int opt, int exit);

#endif
