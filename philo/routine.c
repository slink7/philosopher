/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:59:41 by scambier          #+#    #+#             */
/*   Updated: 2024/04/07 03:04:57 by scambier         ###   ########.fr       */
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
	while (1)
	{
		pthread_mutex_lock(forks_a);
		ft_printf("[%x]%d has taken a fork\n", (forks_a - philo->table->forks), philo->index);
		pthread_mutex_lock(forks_b);
		ft_printf("[%x]%d is eating\n", (forks_b - philo->table->forks), philo->index);
		usleep(philo->params_cpy[TT_EAT] * 1000);
		pthread_mutex_unlock(forks_b);
		pthread_mutex_unlock(forks_a);
		ft_printf("%d is sleeping\n", philo->index);
		usleep(philo->params_cpy[TT_SLEEP] * 1000);

	}
	return (0);
}
