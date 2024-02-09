/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:20:03 by scambier          #+#    #+#             */
/*   Updated: 2024/02/09 16:22:20 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

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
