/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:45:04 by jomunoz           #+#    #+#             */
/*   Updated: 2025/09/10 19:44:38 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meals_eaten(t_data *data, int index)
{
	if (data->cycle_nbr > 0)
	{
		pthread_mutex_lock(&data->meals_mutex);
		if (data->philo[index].eaten_meals < data->cycle_nbr)
			data->meal_flag = 0;
		if (index == data->philo_nbr - 1 && data->meal_flag == 1)
			return (data->stop_flag = 1, 1);
		pthread_mutex_unlock(&data->meals_mutex);
	}
	return (0);
}

static void	save_lines(t_data *data)
{
	pthread_mutex_unlock(&data->meals_mutex);
	pthread_mutex_lock(&data->print_mutex);
}

static void	*monitor_routine(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		data->meal_flag = 1;
		while (i < data->philo_nbr)
		{
			pthread_mutex_lock(&data->meals_mutex);
			if (now_ms() > data->philo[i].time_to_live)
			{
				save_lines(data);
				data->stop_flag = 1;
				printf("%lu %d %s", elapsed_ms(&data->philo[i]),
					data->philo[i].id, DIED);
				return (pthread_mutex_unlock(&data->print_mutex), NULL);
			}
			pthread_mutex_unlock(&data->meals_mutex);
			if (check_meals_eaten(data, i))
				return (NULL);
			i++;
		}
		usleep(250);
	}
	return (NULL);
}

static int	thread_creation(t_data *data)
{
	int	i;

	i = 0;
	data->start = now_ms();
	while (i < data->philo_nbr)
	{
		data->philo[i].time_to_live = data->start + data->time_die;
		if (pthread_create(&data->philo[i].thread, NULL, (void *)start_routine,
				&data->philo[i]) != 0)
		{
			write(2, "Error: Thread creation failed\n", 31);
			return (1);
		}
		i++;
	}
	if (pthread_create(&data->monitor, NULL, (void *)monitor_routine,
			data) != 0)
	{
		write(2, "Error: Thread creation failed\n", 31);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	static t_data	data;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error: Invalid number of arguments\n", 36);
		return (1);
	}
	if (assignments(argc, argv, &data))
		return (free_all(&data), 1);
	if (thread_creation(&data))
		return (free_all(&data), 1);
	if (thread_joining(&data))
		return (free_all(&data), 1);
	return (free_all(&data), 0);
}
