/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:54:48 by scambier          #+#    #+#             */
/*   Updated: 2024/08/14 17:19:53 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

#include "header.h"

int	set_table(t_table *table)
{
	int	k;

	table->forks = ft_calloc(table->params[COUNT], sizeof(t_mutex));
	if (!table->forks)
		return (0);
	k = -1;
	while (++k < (int)table->params[COUNT])
		if (pthread_mutex_init(table->forks + k, 0))
			return (0);
	return (1);
}

int	clear_table(t_table *table)
{
	int	k;

	k = -1;
	while (++k < (int)table->params[COUNT])
		pthread_mutex_destroy(table->forks + k);
	free(table->forks);
	return (1);
}



void	init_philosopher(t_table *table, t_philosopher *philo)
{
	static int	counter = 0;

	philo->id = counter++;
	philo->table = table;
	mint_init(&philo->stop, 0);
	mint_init(&philo->last_meal, get_ms_ts());
	ft_memcpy(philo->params_cpy, table->params, sizeof(t_params));
	if (pthread_create(&philo->thread, 0, (void *(*)(void *)) routine, philo))
		return ;
}

void	summon_philosophers(t_table *table)
{
	int	k;

	table->philosophers = ft_calloc(table->params[COUNT], sizeof(t_philosopher));
	k = -1;
	while (++k < (int)table->params[COUNT])
		init_philosopher(table, table->philosophers + k);
}

void	wait_for_philosophers(t_table *table)
{
	int	k;

	k = -1;
	while ((unsigned int)++k < table->params[COUNT])
		pthread_join(table->philosophers[k].thread, 0);
	free(table->philosophers);
}
