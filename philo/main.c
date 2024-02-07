/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:07:41 by scambier          #+#    #+#             */
/*   Updated: 2024/02/07 17:06:12 by scambier         ###   ########.fr       */
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

void	deploy_philosophers(void *(*routine)(void *), int	count)
{
	pthread_t	*philosophers;
	int	k;

	philosophers = malloc(sizeof(pthread_t) * count);
	if (!philosophers)
		return ;
	k = -1;
	while (++k < count)
		pthread_create(philosophers + k, 0, routine, (void *)0 + k);
	while (--k >= 0)
		pthread_join(philosophers[k], 0);
}

int	main(int argc, char **argv)
{
	int			k;

	srand(time(0));
	deploy_philosophers(routine, 10);
	return (0);
}