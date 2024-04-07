/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:59:41 by scambier          #+#    #+#             */
/*   Updated: 2024/04/07 15:30:38 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "header.h"

void	*routine(void *arg)
{
	t_philosopher	*philo;
	t_mutex			*forks_a;
	t_mutex			*forks_b;
	int				ate_count;

	ate_count = 0;
	philo = (t_philosopher *)arg;
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
	while (philo->params_cpy[NOTEPME] == 0 || ate_count < philo->params_cpy[NOTEPME])
	{
		pthread_mutex_lock(forks_a);
		ft_printf("[%x]%d has taken a fork\n", (forks_a - philo->table->forks), philo->index);
		pthread_mutex_lock(forks_b);
		ft_printf("[%x]%d is eating\n", (forks_b - philo->table->forks), philo->index);
		usleep(philo->params_cpy[TT_EAT] * 1000);
		ate_count++;
		ft_printf("%d is sleeping\n", philo->index);
		pthread_mutex_unlock(forks_b);
		pthread_mutex_unlock(forks_a);
		usleep(philo->params_cpy[TT_SLEEP] * 1000);

	}
	return (0);
}
