/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:59:41 by scambier          #+#    #+#             */
/*   Updated: 2024/04/06 03:22:20 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "header.h"

void	*routine(void *arg)
{
	t_philosopher	*philo;
	char			*temp;

	philo = (t_philosopher *)arg;
	temp = ft_sprintf("ABC [%d] \t.\n", philo->index);
	write(1, temp, ft_strlen(temp) + 1);
	free(temp);
	sleep(1);
	return (0);
}
