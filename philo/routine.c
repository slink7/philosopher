/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:59:41 by scambier          #+#    #+#             */
/*   Updated: 2024/05/02 15:32:14 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "header.h"

static unsigned int	get_age(t_philosopher *philo)
{
	return (get_ms_ts() - philo->params_cpy[START_DATE]);
}

int	check_death(t_philosopher *philo)
{
	if (mutint_get(&philo->stop))
		return (1);
	if (get_ms_ts() - philo->last_meal_date < philo->params_cpy[TT_DIE])
		return (0);
	ft_printf("[%d] %d has died (intern)!\n", get_age(philo), philo->index);
	return (1);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;
	t_mutex			*forks_a;
	t_mutex			*forks_b;
	unsigned int	ate_count;

	ate_count = 0;
	philo = (t_philosopher *)arg;
	philo->last_meal_date = get_ms_ts();
	if (philo->index == 0)
	{
		forks_a = &philo->table->forks[(philo->index + 1) % philo->params_cpy[SIZE]];
		forks_b = &philo->table->forks[philo->index];
	}
	else
	{
		forks_a = &philo->table->forks[philo->index];
		forks_b = &philo->table->forks[(philo->index + 1) % philo->params_cpy[SIZE]];
	}
	while (1)
	{
		pthread_mutex_lock(forks_a);
		//A
		if (check_death(philo))
			break;
		ft_printf("[%u] %d has taken a fork\n", get_age(philo), philo->index);
		pthread_mutex_lock(forks_b);
		//B
		if (check_death(philo))
			break;
		ft_printf("[%u] %d is eating\n", get_age(philo), philo->index);
		philo->last_meal_date = get_ms_ts();
		usleep(philo->params_cpy[TT_EAT] * 1000);
		ate_count++;
		pthread_mutex_unlock(forks_b);
		pthread_mutex_unlock(forks_a);
		if (philo->params_cpy[NOTEPME] > 0 && ate_count > philo->params_cpy[NOTEPME])
			break ;
		ft_printf("[%u] %d is sleeping\n", get_age(philo), philo->index);
		//C
		if (check_death(philo))
			break;
		usleep(philo->params_cpy[TT_SLEEP] * 1000);
	}
	mutint_set(&philo->has_stopped, 1);
	ft_printf("%d exited\n", philo->index);
	return (0);
}
