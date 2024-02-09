/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:50:35 by scambier          #+#    #+#             */
/*   Updated: 2024/02/09 16:59:17 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "philosopher.h"

unsigned int	get_ms_ts();

int	eat(t_philosopher *philo, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	pthread_mutex_lock(left_fork);
	pthread_mutex_lock(right_fork);

	if (get_has_died(philo->table))
	{
		pthread_mutex_unlock(right_fork);
		pthread_mutex_unlock(left_fork);
		return (0);
	}

	pthread_mutex_lock(&philo->table->log);
	printf("[%6ums] - %2d eats\n", get_ms_ts() - philo->table->start_date, philo->id);
	pthread_mutex_unlock(&philo->table->log);

	set_last_meal_date(philo, get_ms_ts());
	
	usleep(philo->table->time_to_eat * 1000);

	set_last_meal_date(philo, get_ms_ts());

	pthread_mutex_unlock(right_fork);
	pthread_mutex_unlock(left_fork);
	return (1);
}

void	*philosophers_routine(void *arg)
{
	t_philosopher	*philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	philo = (t_philosopher *)arg;
	right_fork = &philo->table->forks[philo->id];
	left_fork = &philo->table->forks[(philo->id + 1) % philo->table->philo_count];
	if (philo->id % 2)
	{
		left_fork = &philo->table->forks[philo->id];
		right_fork = &philo->table->forks[(philo->id + 1) % philo->table->philo_count];
	}
	while (1)
	{
		if (!eat(philo, left_fork, right_fork))
			return (0);
			
		if (get_has_died(philo->table))
			return (0);

		pthread_mutex_lock(&philo->table->log);
		printf("[%6ums] - %2d sleeps\n", get_ms_ts() - philo->table->start_date, philo->id);
		pthread_mutex_unlock(&philo->table->log);

		usleep(philo->table->time_to_sleep * 1000);

		if (get_has_died(philo->table))
			return (0);

		pthread_mutex_lock(&philo->table->log);
		printf("[%6ums] - %2d thinks\n", get_ms_ts() - philo->table->start_date, philo->id);
		pthread_mutex_unlock(&philo->table->log);
	}
	return (0);
}
