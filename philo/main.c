/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:07:41 by scambier          #+#    #+#             */
/*   Updated: 2024/02/07 18:46:38 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

typedef struct s_table {
	pthread_mutex_t	*forks;
	int	start_date;
	int	time_to_sleep;
	int	time_to_eat;
	int	philo_count;
}	t_table;

typedef struct s_philosopher {
	int			id;
	int			last_meal_date;
	pthread_t	thread;
	t_table		*table;
}	t_philosopher;



void	*routine(t_philosopher *philo)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	left_fork = &philo->table->forks[philo->id];
	right_fork = &philo->table->forks[(philo->id + 1) % philo->table->philo_count];
	while (1)
	{
		pthread_mutex_lock(left_fork);
		pthread_mutex_lock(right_fork);
		printf("[%6d]Philo %2d eats\n", get_time() - philo->table->start_date, philo->id);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_unlock(right_fork);
		pthread_mutex_unlock(left_fork);
		printf("[%6d]Philo %2d sleeps\n", get_time() - philo->table->start_date, philo->id);
		usleep(philo->table->time_to_sleep * 1000);
		printf("[%6d]Philo %2d thinks\n", get_time() - philo->table->start_date, philo->id);
	}
	return (0);
}

void	deploy_philosophers(t_table *table, void *(*routine)(void *))
{
	t_philosopher	*philosophers;
	int	k;

	philosophers = malloc(sizeof(t_philosopher) * table->philo_count);
	if (!philosophers)
		return ;
	k = -1;
	while (++k < table->philo_count)
	{
		philosophers[k].id = k;
		philosophers[k].table = table;
		pthread_create(&philosophers[k].thread, 0, routine, philosophers + k);
	}
	while (--k >= 0)
		pthread_join(philosophers[k].thread, 0);
}

void	set_table(t_table *table)
{
	int	k;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!table->forks)
		return ;
	k = -1;
	while (++k < table->philo_count)
		pthread_mutex_init(table->forks + k, 0);
}

void	clear_table(t_table *table)
{
	int	k;

	k = -1;
	while (++k < table->philo_count)
		pthread_mutex_destroy(table->forks + k);
	free(table->forks);
}

int	get_time()
{
	static struct timeval tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	main(int argc, char **argv)
{
	t_table table;

	table.start_date = get_time();
	table.philo_count = 3;
	table.time_to_eat = 123;
	table.time_to_sleep = 1234;
	set_table(&table);
	deploy_philosophers(&table, routine);
	clear_table(&table);
	return (0);
}