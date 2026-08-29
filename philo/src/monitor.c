/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltong <ltong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 11:40:44 by ltong             #+#    #+#             */
/*   Updated: 2026/08/29 16:48:34 by ltong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_ate_enough(t_table *table)
{
	int	i;

	if (table->must_eat < 0)
		return (FALSE);
	i = 0;
	while (i < table->philo_count)
	{
		if (table->philos[i].meals_eaten < table->must_eat)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	check_death(t_table *table, int *dead_id)
{
	int		i;
	long	now;

	i = 0;
	now = get_time_ms();
	while (i < table->philo_count)
	{
		if (now - table->philos[i].last_meal >= table->time_to_die)
		{
			table->stop = TRUE;
			*dead_id = table->philos[i].id;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static int	check_state(t_table *table, int *dead_id)
{
	pthread_mutex_lock(&table->state_lock);
	if (check_death(table, dead_id) == TRUE)
	{
		pthread_mutex_unlock(&table->state_lock);
		return (TRUE);
	}
	if (all_ate_enough(table) == TRUE)
		table->stop = TRUE;
	pthread_mutex_unlock(&table->state_lock);
	return (FALSE);
}

void	monitor(t_table *table)
{
	int	dead_id;

	while (get_stop(table) == FALSE)
	{
		dead_id = 0;
		if (check_state(table, &dead_id) == TRUE)
		{
			pthread_mutex_lock(&table->print_lock);
			printf("%ld %d died\n", elapsed_time(table), dead_id);
			pthread_mutex_unlock(&table->print_lock);
			return ;
		}
		usleep(500);
	}
}
