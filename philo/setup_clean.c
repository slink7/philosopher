/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:58:39 by scambier          #+#    #+#             */
/*   Updated: 2024/05/30 14:06:39 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "header.h"

int	set_table(t_table *table)
{
	int	k;

	table->forks = ft_calloc(table->params[SIZE], sizeof(t_mutex));
	if (!table->forks)
		return (0);
	k = -1;
	while ((unsigned int)++k < table->params[SIZE])
		if (pthread_mutex_init(table->forks + k, 0))
			return (0);
	return (1);
}

int	clear_table(t_table *table)
{
	int	k;

	k = -1;
	while ((unsigned int)++k < table->params[SIZE])
		if (pthread_mutex_destroy(table->forks + k))
			return (0);
	free(table->forks);
	return (1);
}

static int	init_philosopher(t_philosopher *philo, t_table *table)
{
	static int	counter = 0;

	philo->index = counter++;
	philo->table = table;
	philo->last_meal = get_ms_ts();
	ft_memcpy(philo->params_cpy, table->params, sizeof(t_params));
	if (pthread_create(&philo->thread, 0, (void *)routine, philo))
		return (ft_fprintf(2, "Error: pthread_create failed\n") & 0);
	return (1);
}

int	summon_philosophers(t_table *table)
{
	int	k;

	table->philosophers = ft_calloc(table->params[SIZE], sizeof(t_philosopher));
	if (!table->philosophers)
		return (ft_fprintf(2, "Error: malloc failed\n") & 0);
	k = -1;
	while ((unsigned int)++k < table->params[SIZE])
		if (!init_philosopher(table->philosophers + k, table))
			return (0);
	return (1);
}

void	wait_for_philosophers(t_table *table)
{
	int	k;

	k = -1;
	while ((unsigned int)++k < table->params[SIZE])
		pthread_join(table->philosophers[k].thread, 0);
	free(table->philosophers);
}
