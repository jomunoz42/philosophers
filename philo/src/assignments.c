/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:27:51 by jomunoz           #+#    #+#             */
/*   Updated: 2025/10/02 19:48:45 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_numbers(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				write(2, "Error: Non numeric argument\n", 29);
				return (1);
			}
			j++;
		}
		i++;
	}
}

static int	assign_args(int argc, char **argv, t_data *data)
{
	if (check_numbers(argv) == 1)
		return (1);
	data->philo_nbr = ft_atoi(argv[1]);
	if (data->philo_nbr <= 0 || data->philo_nbr > 200)
		return (write(2, "Error: Invalid number of philosophers\n", 39), 1);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->cycle_nbr = ft_atoi(argv[5]);
	else
		data->cycle_nbr = -1;
	if (data->time_die < 60 || data->time_eat < 60 || data->time_sleep < 60)
		return (write(2, "Error: Invalid argument\n", 25), 1);
	if (data->cycle_nbr == 0)
		return (1);
	return (0);
}

static int	assign_mallocs(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philo)
		return (write(2, "Error: Allocation failed\n", 26), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	if (!data->forks)
		return (write(2, "Error: Allocation failed\n", 26), 1);
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (write(2, "Error: Mutex creation failed\n", 29), 1);
		i++;
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (write(2, "Error: Mutex creation failed\n", 30), 1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (write(2, "Error: Mutex creation failed\n", 30), 1);
	if (pthread_mutex_init(&data->meals_mutex, NULL) != 0)
		return (write(2, "Error: Mutex creation failed\n", 30), 1);
	return (0);
}

static void	assign_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		data->philo[i].id = i + 1;
		if (i % 2 != 0)
		{
			data->philo[i].left = &data->forks[i];
			data->philo[i].right = &data->forks[(i + 1) % data->philo_nbr];
		}
		else
		{
			data->philo[i].left = &data->forks[(i + 1) % data->philo_nbr];
			data->philo[i].right = &data->forks[i];
		}
		data->philo[i].eaten_meals = 0;
		data->philo[i].data = data;
		i++;
	}
}

int	assignments(int argc, char **argv, t_data *data)
{
	if (assign_args(argc, argv, data) == 1)
		return (1);
	if (data->philo_nbr == 1)
	{
		printf("%d %d %s", 0, 1, FORK);
		printf("%d %d %s", data->time_die, 1, DIED);
		return (1);
	}
	if (assign_mallocs(data) == 1)
		return (1);
	assign_philos(data);
	return (0);
}
