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

# define FREE_BASIC	1
# define FREE_PHILO	2
# define DSTROY_FRK	4

//	INCLUDES

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

//	STRUCTS

// Forks Struct Array
typedef struct s_fork
{
	int				taken;
	pthread_mutex_t	mutex;
}	t_fork;

// Philosophers Struct Array
typedef struct s_philo
{
	pthread_t		th;
	int				id;
	int				meals;
	pthread_mutex_t	meals_m;
	long			last_meal;
	pthread_mutex_t	last_meal_m;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_ph		*ph;
}	t_philo;

// Main Struct
typedef struct s_ph
{
	pthread_t		monitor;
	long			start_t;
	int				ph_cnt;
	int				frk_cnt;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_meals;
	pthread_mutex_t	print;
	int				philo_died;
	pthread_mutex_t	philo_died_m;	
	t_fork			*forks;
	t_philo			*philo;
}	t_ph;

//	FUNCS

// Initialization
int		init_phil(t_ph *ph, char **argv);
int		create_philos(t_ph *ph);

// Threads
void	*monitor(void *arg);
void	*rout(void *arg);
int		check_meals(t_ph *ph);

// Routine
void	thinking(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
int		time_to_eat(t_philo *philo);

// Mutex Handlers
int		death(t_ph *ph, int status);
long	last_meal(t_philo *philo, long timecode);
int		meals(t_philo *philo, int status);
int		checkfork(t_fork *fork);
void	releasefork(t_fork *fork);

// Utils
long	ft_get_time(void);
void	ft_print(t_philo *philo, char *msg);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// Memmory Cleanup
int		free_mem(t_ph *ph, int opt, int exit);

#endif
