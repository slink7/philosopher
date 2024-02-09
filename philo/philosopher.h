/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:51:03 by scambier          #+#    #+#             */
/*   Updated: 2024/02/09 16:51:02 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>

typedef struct s_philosopher	t_philosopher;

typedef struct s_table {
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log;
	pthread_mutex_t	schrodinger;
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
	pthread_mutex_t	mutex;
	t_table			*table;
}	t_philosopher;

void			*philosophers_routine(void *arg);
int				get_has_died(t_table *table);
void			set_has_died(t_table *table, int has_died);
unsigned int	get_last_meal_date(t_philosopher *philo);
void			set_last_meal_date(t_philosopher *philo, unsigned int last_meal_date);

#endif