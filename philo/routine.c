/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:14:09 by scambier          #+#    #+#             */
/*   Updated: 2024/08/22 14:09:41 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

#include "header.h"

static int	philo_eat(t_philosopher *philo, t_mutex *lfork, t_mutex *rfork)
{
	pthread_mutex_lock(lfork);
	if (mint_get(&philo->stop))
	{
		pthread_mutex_unlock(lfork);
		return (0);
	}
	ft_printf("%d %d has taken a fork\n", get_age(philo), philo->id);
	pthread_mutex_lock(rfork);
	if (mint_get(&philo->stop))
	{
		pthread_mutex_unlock(rfork);
		pthread_mutex_unlock(lfork);
		return (0);
	}
	ft_printf("%d %d is eating\n", get_age(philo), philo->id);
	mint_set(&philo->last_meal, get_ms_ts());
	usleep(philo->params_cpy[TT_EAT] * 1000);
	pthread_mutex_unlock(rfork);
	pthread_mutex_unlock(lfork);
	return (1);
}

void	*routine(t_philosopher *philo)
{
	int		eat_count;
	t_mutex	*left_fork;
	t_mutex	*right_fork;

	left_fork = &philo->table->forks[philo->id];
	right_fork = &philo->table->forks[(philo->id + 1)
		% philo->table->params[COUNT]];
	usleep(philo->id * 200 + (philo->id % 2) * 400 + 1000);
	eat_count = 0;
	while (eat_count++ < (int) philo->params_cpy[NOTEPME])
	{
		if (mint_get(&philo->stop))
			break ;
		ft_printf("%d %d is thinking\n", get_age(philo), philo->id);
		if (!philo_eat(philo, left_fork, right_fork))
			break ;
		if (mint_get(&philo->stop))
			break ;
		ft_printf("%d %d is sleeping\n", get_age(philo), philo->id);
		usleep(philo->params_cpy[TT_SLEEP] * 1000);
	}
	mint_set(&philo->stop, 1);
	return (0);
}

void	*egoists_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	ft_printf("%d %d is thinking\n", get_age(philo), philo->id);
	ft_printf("%d %d has taken a fork\n", get_age(philo), philo->id);
	while (!mint_get(&philo->stop))
		usleep(50000);
	return (0);
}
