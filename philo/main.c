/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:07:41 by scambier          #+#    #+#             */
/*   Updated: 2024/08/14 16:48:02 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "header.h"


static int	read_argv(t_table *table, int argc, char **argv)
{
	int	k;

	if (argc < 4 || argc > 5)
		return (ft_fprintf(2, "Error: wrong number of args\n") & 0);
	table->params[NOTEPME] = 0x7FFFFFFF;
	k = -1;
	while (++k < argc)
		if (!ft_atoi_strict((int *)table->params + k, argv[k]))
			return (ft_fprintf(2, "Error: \"%s\" is invalid\n", argv[k]) & 0);
	return (1);
}

int	is_dead(t_philosopher *philo)
{
	return (get_ms_ts() - mint_get(&philo->last_meal) > philo->table->params[TT_DIE]);
}
void	*grim_reaper(t_table *table)
{
	t_philosopher	*philo;
	int				k;

	k = 0;
	while (1)
	{
		philo = table->philosophers + (k++ % table->params[COUNT]);
		if (is_dead(philo))
		{
			ft_printf("%d %d died\n", get_age(philo), philo->id, get_ms_ts() - mint_get(&philo->last_meal));
			break ;
		}
	}
	k = -1;
	while (++k < (int)table->params[COUNT])
		mint_set(&table->philosophers[k].stop, 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	ft_memset(&table, 0, sizeof(table));
	if (!read_argv(&table, argc - 1, argv + 1))
		return (1);
	if (!set_table(&table))
		return (1);
	table.start = get_ms_ts();
	summon_philosophers(&table);

	pthread_create(&table.grim_reaper, 0, (void *(*)(void *))grim_reaper, &table);

	wait_for_philosophers(&table);
	pthread_detach(table.grim_reaper);
	clear_table(&table);
	return (0);
}