/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:59:41 by scambier          #+#    #+#             */
/*   Updated: 2024/05/02 16:36:37 by scambier         ###   ########.fr       */
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
	if (!mutint_get(&philo->table->stop))
	{
		if (get_ms_ts() - philo->last_meal_date < philo->params_cpy[TT_DIE])
			return (0);
		mutint_set(&philo->table->stop, 1);
		ft_printf("[%d] %d has died (intern)!\n", get_age(philo), philo->index);
	}
	return (1);
}

void	ft_swap(void **a, void **b)
{
	void	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
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
	forks_a = &philo->table->forks[philo->index];
	forks_b = &philo->table->forks[(philo->index + 1) % philo->params_cpy[SIZE]];
	if (philo->index % 2 == 0)
		ft_swap((void **)&forks_a, (void **)&forks_b);
	while (1)
	{
		pthread_mutex_lock(forks_a);
		if (check_death(philo))
		{
			pthread_mutex_unlock(forks_a);
			break;
		}
		ft_printf("[%u] %d has taken a fork\n", get_age(philo), philo->index);
		pthread_mutex_lock(forks_b);
		if (check_death(philo))
		{
			pthread_mutex_unlock(forks_a);
			pthread_mutex_unlock(forks_b);
			break;
		}
		ft_printf("[%u] %d is eating\n", get_age(philo), philo->index);
		philo->last_meal_date = get_ms_ts();
		usleep(philo->params_cpy[TT_EAT] * 1000);
		ate_count++;
		pthread_mutex_unlock(forks_a);
		pthread_mutex_unlock(forks_b);
		if (philo->params_cpy[NOTEPME] > 0 && ate_count > philo->params_cpy[NOTEPME])
			break ;
		if (check_death(philo))
			break;
		ft_printf("[%u] %d is sleeping\n", get_age(philo), philo->index);
		usleep(philo->params_cpy[TT_SLEEP] * 1000);
	}
	ft_printf("%d exited\n", philo->index);
	return (0);
}
