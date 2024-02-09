/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:07:41 by scambier          #+#    #+#             */
/*   Updated: 2024/02/09 17:06:02 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#include "utils.h"
#include "philosopher.h"

void	deploy_philosophers(t_table *table, void *(*routine)(void *))
{
	int	k;

	table->philosophers = malloc(sizeof(t_philosopher) * table->philo_count);
	if (!table->philosophers)
		return ;
	k = -1;
	while (++k < table->philo_count)
	{
		table->philosophers[k].id = k;
		table->philosophers[k].table = table;
		table->philosophers[k].last_meal_date = get_ms_ts();
		pthread_mutex_init(&table->philosophers[k].mutex, 0);
		pthread_create(&table->philosophers[k].thread, 0, routine, table->philosophers + k);
	}
}

void	clean_the_spaghetti(t_table *table)
{
	int	k;

	k = -1;
	while (++k < table->philo_count)
		pthread_join(table->philosophers[k].thread, 0);
	free(table->philosophers);
}

void	set_table(t_table *table)
{
	int	k;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!table->forks)
		return ;
	k = -1;
	while (++k < table->philo_count)
		pthread_mutex_init(table->forks + k, 0);
	pthread_mutex_init(&table->schrodinger, 0);
	pthread_mutex_init(&table->log, 0);
}

void	clear_table(t_table *table)
{
	int	k;

	k = -1;
	while (++k < table->philo_count)
		pthread_mutex_destroy(table->forks + k);
	free(table->forks);
	pthread_mutex_destroy(&table->schrodinger);
	pthread_mutex_destroy(&table->log);
}

void	ft_grim_reaper(t_table *table)
{
	unsigned int	current_date;
	int	k;

	current_date = get_ms_ts();
	k = -1;
	while (++k < table->philo_count)
	{
		if (current_date - get_last_meal_date(&table->philosophers[k]) >= table->time_to_die)
		{
			set_has_died(table, 1);
			pthread_mutex_lock(&table->log);
			printf("Philosopher#%d died :'(\n", k);
			pthread_mutex_unlock(&table->log);
			break ;
		}
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	table.has_died = 0;
	table.start_date = get_ms_ts();
	table.philo_count = ft_atoi(argv[1]);
	table.time_to_die = ft_atoi(argv[2]);
	table.time_to_eat = ft_atoi(argv[3]);
	table.time_to_sleep = ft_atoi(argv[4]);
	set_table(&table);
	deploy_philosophers(&table, philosophers_routine);
	while (!table.has_died)
		ft_grim_reaper(&table);
	clean_the_spaghetti(&table);
	clear_table(&table);
	return (0);
}
