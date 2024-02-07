/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:07:41 by scambier          #+#    #+#             */
/*   Updated: 2024/02/07 21:13:59 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

typedef struct s_philosopher	t_philosopher;

typedef struct s_table {
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	int				has_died;
	unsigned int	start_date;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				philo_count;
}	t_table;

typedef struct s_philosopher {
	int				id;
	unsigned int	last_meal_date;
	pthread_t		thread;
	t_table			*table;
}	t_philosopher;

static int	ft_isdigit(const char c)
{
	return (c >= '0' && c <= '9');
}

static int	tvnrf(char *c)
{
	return ((*c < 9 || *c > 13) && *c != 32);
}

int	ft_atoi(const char *nptr)
{
	long	out;
	int		sign;

	out = 0;
	sign = 1;
	while (!tvnrf((char *)nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr)
	{
		if (!ft_isdigit(*nptr))
			break ;
		out = out * 10 + *nptr - '0';
		nptr++;
	}
	return (out * sign);
}

int	get_ms_ts(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	philo = (t_philosopher *)arg;
	left_fork = &philo->table->forks[philo->id];
	right_fork = &philo->table->forks[(philo->id + 1) % philo->table->philo_count];
	while (1)
	{
		pthread_mutex_lock(left_fork);
		pthread_mutex_lock(right_fork);
		if (philo->table->has_died)
		{
			pthread_mutex_unlock(right_fork);
			pthread_mutex_unlock(left_fork);
			return (0);
		}
		printf("[%6ums] - %2d eats\n", get_ms_ts() - philo->table->start_date, philo->id);
		philo->last_meal_date = get_ms_ts();
		usleep(philo->table->time_to_eat * 1000);
		philo->last_meal_date = get_ms_ts();
		pthread_mutex_unlock(right_fork);
		pthread_mutex_unlock(left_fork);
		if (philo->table->has_died)
			return (0);
		printf("[%6ums] - %2d sleeps\n", get_ms_ts() - philo->table->start_date, philo->id);
		usleep(philo->table->time_to_sleep * 1000);
		if (philo->table->has_died)
			return (0);
		printf("[%6ums] - %2d thinks\n", get_ms_ts() - philo->table->start_date, philo->id);
	}
	return (0);
}

void	deploy_philosophers(t_table *table, void *(*routine)(void *))
{
	int	k;

	table->philosophers = malloc(sizeof(t_philosopher) * table->philo_count);
	if (!table->philosophers)
		return ;
	k = -1;
	while (++k < table->philo_count)
	{
		table->philosophers[k].id = k;
		table->philosophers[k].table = table;
		table->philosophers[k].last_meal_date = get_ms_ts();
		pthread_create(&table->philosophers[k].thread, 0, routine, table->philosophers + k);
	}
}

void	clean_the_spaghetti(t_table *table)
{
	int	k;

	k = -1;
	while (++k < table->philo_count)
		pthread_join(table->philosophers[k].thread, 0);
	free(table->philosophers);
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

void	ft_grim_reaper(t_table *table)
{
	unsigned int	current_date;
	int	k;

	current_date = get_ms_ts();
	k = -1;
	while (++k < table->philo_count)
	{
		if (current_date - table->philosophers[k].last_meal_date >= table->time_to_die)
			table->has_died++;
		if (table->has_died)
		{
			printf("Philosopher#%d died :'(\n", k);
			break ;
		}
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	table.has_died = 0;
	table.start_date = get_ms_ts();
	table.philo_count = ft_atoi(argv[1]);
	table.time_to_die = ft_atoi(argv[2]);
	table.time_to_eat = ft_atoi(argv[3]);
	table.time_to_sleep = ft_atoi(argv[4]);
	set_table(&table);
	deploy_philosophers(&table, routine);
	while (!table.has_died)
		ft_grim_reaper(&table);
	clean_the_spaghetti(&table);
	clear_table(&table);
	return (0);
}
