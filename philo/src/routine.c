/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:27:51 by jomunoz           #+#    #+#             */
/*   Updated: 2025/10/01 23:36:31 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_joining(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
		{
			write(2, "Error: Failed to join thread\n", 30);
			return (1);
		}
		i++;
	}
	if (pthread_join(data->monitor, NULL) != 0)
	{
		write(2, "Error: Failed to join thread\n", 30);
		return (1);
	}
	return (0);
}

static int	protected_print(t_philo *p, char *message)
{
	pthread_mutex_lock(&p->data->print_mutex);
	if (p->data->stop_flag)
	{
		pthread_mutex_unlock(&p->data->print_mutex);
		return (1);
	}
	printf("%lu %d %s", elapsed_ms(p), p->id, message);
	pthread_mutex_unlock(&p->data->print_mutex);
	return (0);
}

int	get_forks(t_philo *p)
{
	pthread_mutex_lock(p->left);
	if (p->data->stop_flag)
		return (pthread_mutex_unlock(p->left), 1);
	if (protected_print(p, FORK))
		return (pthread_mutex_unlock(p->left), 1);
	pthread_mutex_lock(p->right);
	if (p->data->stop_flag)
	{
		pthread_mutex_unlock(p->left);
		pthread_mutex_unlock(p->right);
		return (1);
	}
	if (protected_print(p, FORK))
	{
		pthread_mutex_unlock(p->left);
		pthread_mutex_unlock(p->right);
		return (1);
	}
	pthread_mutex_lock(&p->data->meals_mutex);
	p->time_to_live = now_ms() + p->data->time_die;
	p->eaten_meals++;
	pthread_mutex_unlock(&p->data->meals_mutex);
	return (0);
}

void	*start_routine(t_philo *p)
{
	if (p->data->philo_nbr % 2 == 0)
	{
		if (p->id % 2 != 0)
			my_sleep(p->data->time_eat);
	}
	while (1)
	{
		if (get_forks(p))
			return (NULL);
		if (protected_print(p, EAT))
		{
			pthread_mutex_unlock(p->left);
			pthread_mutex_unlock(p->right);
			return (NULL);
		}
		my_sleep(p->data->time_eat);
		pthread_mutex_unlock(p->left);
		pthread_mutex_unlock(p->right);
		if (protected_print(p, SLEEP))
			return (NULL);
		my_sleep(p->data->time_sleep);
		if (protected_print(p, THINK))
			return (NULL);
	}
	return (NULL);
}
