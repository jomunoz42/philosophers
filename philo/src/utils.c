/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 19:01:05 by jomunoz           #+#    #+#             */
/*   Updated: 2025/09/29 21:11:22 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *nb)
{
	int		i;
	int		sign;
	long	num;

	i = 0;
	num = 0;
	while (nb[i] == ' ' || (nb[i] >= 9 && nb[i] <= 13))
		i++;
	sign = (nb[i] != '-') - (nb[i] == '-');
	i += (nb[i] == '-') || (nb[i] == '+');
	while (nb[i] >= '0' && nb[i] <= '9')
		num = num * 10 + (nb[i++] - '0');
	return (num * sign);
}

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

long	elapsed_ms(t_philo *philo)
{
	return (now_ms() - philo->data->start);
}

void	my_sleep(long time)
{
	long	current;

	current = now_ms() + time;
	while (now_ms() < current)
		usleep(250);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->philo_nbr)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->philo)
		free(data->philo);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meals_mutex);
}
