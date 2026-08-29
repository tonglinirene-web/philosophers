/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltong <ltong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 11:41:30 by ltong             #+#    #+#             */
/*   Updated: 2026/08/29 16:49:31 by ltong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_stop(t_table *table)
{
	int	stop;

	pthread_mutex_lock(&table->state_lock);
	stop = table->stop;
	pthread_mutex_unlock(&table->state_lock);
	return (stop);
}

void	set_stop(t_table *table, int value)
{
	pthread_mutex_lock(&table->state_lock);
	table->stop = value;
	pthread_mutex_unlock(&table->state_lock);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (get_stop(philo->table) == FALSE)
		printf("%ld %d %s\n", elapsed_time(philo->table), philo->id, status);
	pthread_mutex_unlock(&philo->table->print_lock);
}
