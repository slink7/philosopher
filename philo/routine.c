/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:14:09 by scambier          #+#    #+#             */
/*   Updated: 2024/08/14 17:29:58 by scambier         ###   ########.fr       */
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
	eat_count = 0;
	while (eat_count++ < (int) philo->params_cpy[NOTEPME])
	{
		if (mint_get(&philo->stop))
			break ;
		ft_printf("%d %d is thinking\n", get_age(philo), philo->id);
		pthread_mutex_lock(left_fork);
		if (mint_get(&philo->stop))
		{
			pthread_mutex_unlock(left_fork);
			break ;
		}
		ft_printf("%d %d has taken a fork\n", get_age(philo), philo->id);
		pthread_mutex_lock(right_fork);
		if (mint_get(&philo->stop))
		{
			pthread_mutex_unlock(right_fork);
			pthread_mutex_unlock(left_fork);
			break ;
		}
		ft_printf("%d %d is eating\n", get_age(philo), philo->id);
		mint_set(&philo->last_meal, get_ms_ts());
		usleep(philo->params_cpy[TT_EAT] * 1000);
		pthread_mutex_unlock(right_fork);
		pthread_mutex_unlock(left_fork);
		if (mint_get(&philo->stop))
			break ;
		ft_printf("%d %d is sleeping\n", get_age(philo), philo->id);
		usleep(philo->params_cpy[TT_SLEEP] * 1000);
	}
	return (0);
}

void	*egoists_routine(t_philosopher *philo)
{
	ft_printf("%d %d is thinking\n", get_age(philo), philo->id);
	ft_printf("%d %d has taken a fork\n", get_age(philo), philo->id);
	while (!mint_get(&philo->stop))
		usleep(50000);
	return (0);
}
