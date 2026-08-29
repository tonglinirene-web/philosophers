/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltong <ltong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 11:41:27 by ltong             #+#    #+#             */
/*   Updated: 2026/08/29 17:19:05 by ltong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->table->state_lock);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->state_lock);
	print_status(philo, "is eating");
	smart_sleep(philo->table, philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	smart_sleep(philo->table, philo->table->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
}

static int	philo_is_full(t_philo *philo)
{
	int	full;

	full = FALSE;
	pthread_mutex_lock(&philo->table->state_lock);
	if (philo->table->must_eat >= 0
		&& philo->meals_eaten >= philo->table->must_eat)
		full = TRUE;
	pthread_mutex_unlock(&philo->table->state_lock);
	return (full);
}

static void	think_delay(t_philo *philo)
{
	long	delay;

	if (philo->table->philo_count % 2 == 0)
		return ;
	delay = philo->table->time_to_eat - philo->table->time_to_sleep + 1;
	if (delay > 0)
		smart_sleep(philo->table, delay);
	else
		usleep(500);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->philo_count == 1)
		return (one_philo(philo), NULL);
	if (philo->id % 2 == 1)
		usleep(500);
	while (get_stop(philo->table) == FALSE)
	{
		if (philo_is_full(philo) == TRUE)
			break ;
		eat(philo);
		if (get_stop(philo->table) == TRUE)
			break ;
		print_status(philo, "is sleeping");
		smart_sleep(philo->table, philo->table->time_to_sleep);
		print_status(philo, "is thinking");
		think_delay(philo);
	}
	return (NULL);
}
