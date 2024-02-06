/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:07:41 by scambier          #+#    #+#             */
/*   Updated: 2024/02/06 16:56:42 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void	*routine(void *arg)
{
	int	sleept;

	sleept = rand() % 3000000;
	usleep(sleept);
	printf("[%4dms]Hello world from thread %d !\n", sleept / 1000, arg);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	*philosophers;
	int			philo_count;
	int			k;

	srand(time(0));
	philo_count = 10;
	philosophers = malloc(sizeof(pthread_t) * philo_count);
	k = -1;
	while (++k < philo_count)
	{
		pthread_create(philosophers + k, 0, routine, (void *)0 + k);
	}
	k = -1;
	while (++k < philo_count)
	{
		pthread_join(philosophers[k], 0);
	}
	return (0);
}