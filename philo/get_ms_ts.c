/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ms_ts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:24:41 by scambier          #+#    #+#             */
/*   Updated: 2024/04/07 17:27:48 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

unsigned int	get_ms_ts(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
