/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:12:23 by scambier          #+#    #+#             */
/*   Updated: 2024/04/06 03:33:36 by scambier         ###   ########.fr       */
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
# define PARAMS_SIZE	5

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef int				t_params[PARAMS_SIZE];

typedef struct s_table	t_table;
typedef struct s_philosopher {
	struct s_table	*table;
	t_thread		thread;
	t_params		params_cpy;
	int				index;
}	t_philosopher;

# define PRINTF			0
# define PUBMUT_SIZE	1

typedef struct s_table {
	t_philosopher	*philosophers;
	t_params		params;
	t_mutex			*forks;
	t_mutex			pubmut[PUBMUT_SIZE];
}	t_table;

//routine.c
void	*routine(void *arg);

//setup_clean.c
int		set_table(t_table *table);
int		clear_table(t_table *table);
int		summon_philosophers(t_table *table);
void	wait_for_philosophers(t_table *table);

#endif