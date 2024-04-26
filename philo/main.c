/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:07:41 by scambier          #+#    #+#             */
/*   Updated: 2024/04/26 11:17:10 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "header.h"

static int	read_argv(t_table *table, int argc, char **argv)
{
	int	k;

	if (argc < 4 || argc > 5)
		return (ft_fprintf(2, "Error: wrong number of args\n") & 0);
	k = -1;
	while (++k < argc)
		if (!ft_atoi_strict(table->params + k, argv[k]))
			return (ft_fprintf(2, "Error: \"%s\" is invalid\n", argv[k]) & 0);
	return (1);
}

#include "unistd.h"

static unsigned int	get_age(t_philosopher *philo)
{
	return (get_ms_ts() - philo->params_cpy[START_DATE]);
}

void	*grim_reaper(void *arg)
{
	t_table	*table;
	int		k;
	int		flag;
	unsigned int	ls;

	table = (t_table *)arg;
	flag = 1;
	while (flag && !mutint_get(&table->stop))
	{
		k = -1;
		while (++k < table->params[SIZE])
		{
			ls = (unsigned int)mutint_get(&table->philosophers[k].last_meal_date);
			if (get_ms_ts() - ls >= (unsigned int) table->params[TT_DIE] && !mutint_get(&table->philosophers[k].has_stopped)) //TODO iic
			{
				mutint_set(&table->philosophers[k].stop, 1);
				ft_printf("[%d] %d has died (%u, %u)\n", get_age(&table->philosophers[k]), k, get_ms_ts() - ls, (unsigned int) table->params[TT_DIE]);
				flag = 0;
			}
			usleep(50000);
		}
	}
	k = -1;
	while (++k < table->params[SIZE])
		mutint_set(&table->philosophers[k].stop, 1);
	ft_printf("//%d %d\n", flag, !mutint_get(&table->stop));
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	ft_memset(&table, 100, sizeof(t_table));
	if (!read_argv(&table, argc - 1, argv + 1))
		return (1);
	if (!set_table(&table))
		return (1);
	table.params[START_DATE] = get_ms_ts();
	table.stop.value = 0;
	pthread_mutex_init(&table.stop.mutex, 0);
	summon_philosophers(&table);
	pthread_create(&table.grim_reaper, 0, grim_reaper, &table);
	wait_for_philosophers(&table);
	mutint_set(&table.stop, 1);
	pthread_join(table.grim_reaper, 0);
	clear_table(&table);
	return (0);
}
