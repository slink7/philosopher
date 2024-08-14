/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:46:51 by scambier          #+#    #+#             */
/*   Updated: 2024/08/14 15:56:18 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_dead(t_philosopher *philo)
{
	return (mint_get(&philo->last_meal) - get_ms_ts() > philo->table->params[TT_DIE]);
}
void	*grim_reaper(t_table *table)
{
	int	k;

	k = 0;
	while (1)
	{
		if (is_dead(table->philosophers + (k++ % table->params[COUNT])))
			break ;
	}
	k = -1;
	while (++k < table->params[COUNT])
		mint_set(&table->philosophers[k].stop, 1);
}