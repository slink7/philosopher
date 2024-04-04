/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:07:41 by scambier          #+#    #+#             */
/*   Updated: 2024/04/05 00:37:05 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef int				t_params[5];

typedef struct s_table	t_table;
typedef struct s_philosopher {
	struct s_table	*table;
	t_thread		thread;
	t_params		params_cpy;
	int				index;
}	t_philosopher;

typedef struct s_table {
	t_mutex			*forks;
	t_philosopher	*philosophers;
	t_params		params;
}	t_table;

#define SIZE 0
#define TT_DIE 1
#define TT_EAT 2
#define TT_SLEEP 3
#define NOTEPME 4

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	printf("Cpy :%d %ld\n", philo->index, philo->thread);
	sleep(1);
	return (0);
}

int	read_argv(t_table *table, int argc, char **argv)
{
	int	k;

	if (argc < 4 || argc > 5)
		return (0);
	k = -1;
	while (++k < argc)
		table->params[k] = ft_atoi(argv[k]);
	return (1);
}

void	init_philosopher(t_philosopher *philo, t_table *table)
{
	static int	counter = 0;

	philo->index = counter++;
	philo->table = table;
	ft_memcpy(philo->params_cpy, table->params, sizeof(t_params));
	pthread_create(&philo->thread, 0, routine, philo);
}

void	wait_for_philosophers(t_table *table)
{
	int	k;

	k = -1;
	while (++k < table->params[SIZE])
		pthread_join(table->philosophers[k].thread, 0);
	free(table->philosophers);
}

void	summon_philosophers(t_table *table)
{
	int	k;

	table->philosophers = ft_calloc(table->params[SIZE], sizeof(t_philosopher));
	k = -1;
	while (++k < table->params[SIZE])
		init_philosopher(table->philosophers + k, table);
}

int	main(int argc, char **argv)
{
	t_table	table;

	(void)argc;
	(void)argv;
	ft_bzero(&table, sizeof(t_table));
	read_argv(&table, argc - 1, argv + 1);
	summon_philosophers(&table);
	wait_for_philosophers(&table);
	
	return (0);
}
