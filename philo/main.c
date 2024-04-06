/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:07:41 by scambier          #+#    #+#             */
/*   Updated: 2024/04/06 02:08:02 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "header.h"

int	main(int argc, char **argv)
{
	t_table	table;

	ft_bzero(&table, sizeof(t_table));
	if (!read_argv(&table, argc - 1, argv + 1))
		return (1);
	if (!set_table(&table))
		return (1);
	summon_philosophers(&table);
	wait_for_philosophers(&table);
	clear_table(&table);
	return (0);
}
