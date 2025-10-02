/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:45:11 by jomunoz           #+#    #+#             */
/*   Updated: 2025/09/30 20:43:07 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define FORK "has taken a fork\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DIED "died\n"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	long				time_to_live;
	int					eaten_meals;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	pthread_t			thread;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					philo_nbr;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					cycle_nbr;
	int					stop_flag;
	int					meal_flag;
	long				start;
	pthread_t			monitor;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		meals_mutex;
	pthread_mutex_t		*forks;
	t_philo				*philo;
}						t_data;

//=====================ASSIGNEMTS===========================

int						assignments(int argc, char **argv, t_data *data);

//========================CORE==============================

int						thread_joining(t_data *data);
void					*start_routine(t_philo *p);

//========================UTILS=============================

int						ft_atoi(char *nb);
long					now_ms(void);
long					elapsed_ms(t_philo *philo);
void					my_sleep(long time);
void					free_all(t_data *data);

#endif