/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:07:41 by scambier          #+#    #+#             */
/*   Updated: 2024/04/04 19:49:02 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef struct s_table	t_table;

typedef struct s_philosopher {
	struct s_table	*table;
	t_thread		thread;
}	t_philosopher;

typedef struct s_table {
	t_mutex			*forks;
	t_philosopher	*philosophers;
	int				table_size;
}	t_table;

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	printf("Henlo %ld :3\n", philo->thread);
	return (0);
}

void	summon_philosophers(t_table *table)
{
	int	k;

	table->philosophers = ft_calloc(table->table_size, sizeof(t_philosopher));
	k = -1;
	while (++k < table->table_size)
	{
		table->philosophers[k].table = table;
		pthread_create(&table->philosophers[k].thread, 0, routine, table->philosophers + k);
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	(void)argc;
	(void)argv;
	table.table_size = 10;
	summon_philosophers(&table);
	return (0);
}
