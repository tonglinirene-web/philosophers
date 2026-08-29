/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltong <ltong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 11:41:33 by ltong             #+#    #+#             */
/*   Updated: 2026/08/29 16:49:43 by ltong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

long	elapsed_time(t_table *table)
{
	return (get_time_ms() - table->start_time);
}

void	smart_sleep(t_table *table, long duration)
{
	long	end;

	end = get_time_ms() + duration;
	while (get_stop(table) == FALSE && get_time_ms() < end)
		usleep(500);
}
