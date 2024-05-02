/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexed_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:11:07 by scambier          #+#    #+#             */
/*   Updated: 2024/05/02 16:03:19 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "header.h"

int	mutint_get(t_mutexed_int *mutint)
{
	int	out;

	pthread_mutex_lock(&mutint->mutex);
	out = mutint->value;
	pthread_mutex_unlock(&mutint->mutex);
	return (out);
}

void	mutint_set(t_mutexed_int *mutint, int value)
{
	pthread_mutex_lock(&mutint->mutex);
	mutint->value = value;
	pthread_mutex_unlock(&mutint->mutex);
}
