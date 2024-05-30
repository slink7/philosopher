/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:59:41 by scambier          #+#    #+#             */
/*   Updated: 2024/05/30 13:53:12 by scambier         ###   ########.fr       */
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

int	check_death(t_philosopher *philo, int ahead)
{
	int	die_in;

	if (!mutint_get(&philo->table->stop))
	{
		die_in = philo->params_cpy[TT_DIE] - (get_ms_ts() - philo->last_meal);
		if (die_in > ahead)
			return (0);
		if (die_in > 0)
			usleep(die_in * 1000);
		if (!mutint_get(&philo->table->stop))
		{
			mutint_set(&philo->table->stop, 1);
			ft_printf("%d %d died\n", get_age(philo), philo->index + 1);
		}
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

int	eat(t_philosopher *philo, t_mutex *fork_a, t_mutex *fork_b)
{
	pthread_mutex_lock(fork_a);
	if (check_death(philo, 0))
	{
		pthread_mutex_unlock(fork_a);
		return (0);
	}
	ft_printf("%u %d has taken a fork\n", get_age(philo), philo->index + 1);
	pthread_mutex_lock(fork_b);
	if (check_death(philo, 0))
	{
		pthread_mutex_unlock(fork_a);
		pthread_mutex_unlock(fork_b);
		return (0);
	}
	ft_printf("%u %d is eating\n", get_age(philo), philo->index + 1);
	philo->last_meal = get_ms_ts() + philo->params_cpy[TT_EAT];
	usleep(philo->params_cpy[TT_EAT] * 1000);
	pthread_mutex_unlock(fork_b);
	pthread_mutex_unlock(fork_a);
	return (1);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;
	t_mutex			*fork_a;
	t_mutex			*fork_b;
	unsigned int	ate_count;

	ate_count = 0;
	philo = (t_philosopher *)arg;
	fork_a = &philo->table->forks[philo->index];
	fork_b = &philo->table->forks[(philo->index + 1) % philo->params_cpy[SIZE]];
	if (philo->index % 2 == 0 && (usleep(philo->params_cpy[TT_EAT] / 2) || 1))
		ft_swap((void **)&fork_a, (void **)&fork_b);
	while (1)
	{
		if (!eat(philo, fork_a, fork_b) || (philo->params_cpy[NOTEPME] > 0
				&& ++ate_count >= philo->params_cpy[NOTEPME]))
			break ;
		ft_printf("%u %d is sleeping\n", get_age(philo), philo->index + 1);
		if (check_death(philo, philo->params_cpy[TT_SLEEP]))
			break ;
		usleep(philo->params_cpy[TT_SLEEP] * 1000);
		if (check_death(philo, philo->params_cpy[TT_SLEEP]))
			break ;
		ft_printf("%u %d is thinking\n", get_age(philo), philo->index + 1);
	}
	return (0);
}

// gere si 1 philo 