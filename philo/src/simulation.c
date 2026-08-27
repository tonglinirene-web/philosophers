/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltong <ltong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 11:41:56 by ltong             #+#    #+#             */
/*   Updated: 2026/08/27 11:41:57 by ltong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_table *table, int created)
{
	int	i;

	i = 0;
	while (i < created)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time_ms();
	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].last_meal = table->start_time;
		if (pthread_create(&table->philos[i].thread, NULL,
				routine, &table->philos[i]) != 0)
		{
			set_stop(table, TRUE);
			join_threads(table, i);
			printf("Error: thread creation failed\n");
			return (FALSE);
		}
		i++;
	}
	monitor(table);
	join_threads(table, table->philo_count);
	return (TRUE);
}

void	cleanup_table(t_table *table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	while (table->forks && i < table->philo_count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->state_lock);
	pthread_mutex_destroy(&table->fork_lock);
	free(table->forks);
	free(table->philos);
}
