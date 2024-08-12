/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:14:09 by scambier          #+#    #+#             */
/*   Updated: 2024/08/12 14:57:13 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

#include "header.h"

void	mutexswp(t_mutex **a, t_mutex **b)
{
	t_mutex	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void *routine(t_philosopher *philo)
{
	int		eat_count;
	t_mutex	*left_fork;
	t_mutex	*right_fork;

	left_fork = &philo->table->forks[philo->id];
	right_fork = &philo->table->forks[(philo->id + 1) % philo->table->params[COUNT]];
	usleep(philo->id * 200 + (philo->id % 2) * 400);
	// if (philo->id % 2 == 0)
	// 	usleep(10000);
		//mutexswp(&left_fork, &right_fork);
	eat_count = 0;
	while (!mint_get(&philo->stop) ^ (eat_count++ >= (int) philo->params_cpy[NOTEPME]))
	{
		ft_printf("%d %d is thinking\n", get_age(philo), philo->id);
		pthread_mutex_lock(left_fork);
		pthread_mutex_lock(right_fork);
		ft_printf("%d %d is eating\n", get_age(philo), philo->id);
		usleep(philo->params_cpy[TT_EAT] * 1000);
		pthread_mutex_unlock(right_fork);
		pthread_mutex_unlock(left_fork);
		ft_printf("%d %d is sleeping\n", get_age(philo), philo->id);
		usleep(philo->params_cpy[TT_SLEEP] * 1000);
	}
	return (0);
}