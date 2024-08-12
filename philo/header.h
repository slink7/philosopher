/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:49:20 by scambier          #+#    #+#             */
/*   Updated: 2024/08/12 14:01:57 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>

# define COUNT			0
# define TT_DIE			1
# define TT_EAT 		2
# define TT_SLEEP		3
# define NOTEPME		4
# define PARAM_COUNT	5

typedef unsigned int	t_params[6];
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef unsigned int	t_date;

typedef struct s_mint {
	t_mutex	mutex;
	int		value;
}	t_mint;

typedef struct s_philosopher {
	struct s_table	*table;
	t_thread		thread;
	t_params		params_cpy;
	int				id;
	t_mint			last_meal;
	t_mint			stop;
}	t_philosopher;


typedef struct s_table {
	t_philosopher	*philosophers;
	t_params		params;
	t_mutex			*forks;
	t_thread		grim_reaper;
	t_date			start;
}	t_table;

//get_ms_ts.c
unsigned int	get_ms_ts(void);
unsigned int	get_age(t_philosopher *philo);

//mint.c
void	mint_init(t_mint *mint, int value);
void	mint_destroy(t_mint *mint);
void	mint_set(t_mint *mint, int value);
int		mint_get(t_mint *mint);

//setup_clean.c
int		set_table(t_table *table);
int		clear_table(t_table *table);
void	*routine(t_philosopher *philo);
void	init_philosopher(t_table *table, t_philosopher *philo);
void	summon_philosophers(t_table *table);
void	wait_for_philosophers(t_table *table);
#endif