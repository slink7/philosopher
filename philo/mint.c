/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mint.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:16:13 by scambier          #+#    #+#             */
/*   Updated: 2024/08/12 11:30:30 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	mint_init(t_mint *mint, int value)
{
	pthread_mutex_init(&mint->mutex, 0);
	mint->value = value;
}

void	mint_destroy(t_mint *mint)
{
	pthread_mutex_destroy(&mint->mutex);
	mint->value = -1;
}

void	mint_set(t_mint *mint, int value)
{
	pthread_mutex_lock(&mint->mutex);
	mint->value = value;
	pthread_mutex_unlock(&mint->mutex);
}

int	mint_get(t_mint *mint)
{
	int	out;

	pthread_mutex_lock(&mint->mutex);
	out = mint->value;
	pthread_mutex_unlock(&mint->mutex);
	return (out);
}
