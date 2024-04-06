/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:07:41 by scambier          #+#    #+#             */
/*   Updated: 2024/04/06 03:26:43 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "header.h"

static int	read_argv(t_table *table, int argc, char **argv)
{
	int	k;

	if (argc < 4 || argc > 5)
	{
		ft_printf_fd(2, "Error: wrong number of args\n");
		return (0);
	}
	k = -1;
	while (++k < argc)
	{
		if (!ft_atoi_strict(table->params + k, argv[k]))
		{
			ft_printf_fd(2, "Error: \"%s\" is invalid\n", argv[k]);
			return (0);
		}
	}
	return (1);
}

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
