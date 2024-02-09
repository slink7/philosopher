/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:38:09 by scambier          #+#    #+#             */
/*   Updated: 2024/02/09 16:51:32 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		get_has_died(t_table *table)
{
	int	out;

	pthread_mutex_lock(&table->schrodinger);
	out = table->has_died;
	pthread_mutex_unlock(&table->schrodinger);
	return (out);
}

void	set_has_died(t_table *table, int has_died)
{
	pthread_mutex_lock(&table->schrodinger);
	table->has_died = has_died;
	pthread_mutex_unlock(&table->schrodinger);
}

unsigned int	get_last_meal_date(t_philosopher *philo)
{
	unsigned int	out;

	pthread_mutex_lock(&philo->mutex);
	out = philo->last_meal_date;
	pthread_mutex_unlock(&philo->mutex);
	return (out);
}

void	set_last_meal_date(t_philosopher *philo, unsigned int last_meal_date)
{
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal_date = last_meal_date;
	pthread_mutex_unlock(&philo->mutex);
}