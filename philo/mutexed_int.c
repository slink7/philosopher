/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexed_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:11:07 by scambier          #+#    #+#             */
/*   Updated: 2024/05/06 20:50:45 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "header.h"

void	mutint_init(t_mutexed_int *mutint, unsigned int val)
{
	mutint->value = val;
	pthread_mutex_init(&mutint->mutex, 0);
}

void	mutint_destroy(t_mutexed_int *mutint)
{
	pthread_mutex_destroy(&mutint->mutex);
}

unsigned int	mutint_get(t_mutexed_int *mutint)
{
	int	out;

	pthread_mutex_lock(&mutint->mutex);
	out = mutint->value;
	pthread_mutex_unlock(&mutint->mutex);
	return (out);
}

void	mutint_set(t_mutexed_int *mutint, unsigned int value)
{
	pthread_mutex_lock(&mutint->mutex);
	mutint->value = value;
	pthread_mutex_unlock(&mutint->mutex);
}
