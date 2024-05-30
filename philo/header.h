/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:12:23 by scambier          #+#    #+#             */
/*   Updated: 2024/05/30 14:31:22 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>

# define SIZE			0
# define TT_DIE			1
# define TT_EAT			2
# define TT_SLEEP		3
# define NOTEPME		4
# define START_DATE		5
# define PARAMS_SIZE	6

typedef unsigned int	t_params[6];
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

typedef struct s_mutexed_int {
	t_mutex	mutex;
	int		value;
}	t_mutexed_int;

typedef struct s_philosopher {
	struct s_table	*table;
	t_thread		thread;
	t_params		params_cpy;
	int				index;
	unsigned int	last_meal;
}	t_philosopher;

typedef struct s_table {
	t_philosopher	*philosophers;
	t_params		params;
	t_mutex			*forks;
	t_thread		grim_reaper;
	t_mutexed_int	stop;
}	t_table;

//routine.c
void			*routine(t_philosopher	*philo);

//setup_clean.c
int				set_table(t_table *table);
int				clear_table(t_table *table);
int				summon_philosophers(t_table *table);
void			wait_for_philosophers(t_table *table);

//get_ms_ts.c
unsigned int	get_ms_ts(void);
unsigned int	get_age(t_philosopher *philo);

//mutexed_int.c
void			mutint_init(t_mutexed_int *mutint, unsigned int val);
void			mutint_destroy(t_mutexed_int *mutint);
unsigned int	mutint_get(t_mutexed_int *mutint);
void			mutint_set(t_mutexed_int *mutint, unsigned int value);

#endif