#include "philo.h"

static int	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (FALSE);
	if (pthread_mutex_init(&table->state_lock, NULL) != 0)
		return (FALSE);
	if (pthread_mutex_init(&table->fork_lock, NULL) != 0)
		return (FALSE);
	return (TRUE);
}

static void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1)
			% table->philo_count];
		table->philos[i].table = table;
		i++;
	}
}

int	init_table(t_table *table)
{
	table->stop = FALSE;
	table->start_time = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->forks || !table->philos)
	{
		printf("Error: malloc failed\n");
		free(table->forks);
		free(table->philos);
		return (FALSE);
	}
	if (init_mutexes(table) == FALSE)
	{
		printf("Error: mutex init failed\n");
		free(table->forks);
		free(table->philos);
		return (FALSE);
	}
	init_philos(table);
	return (TRUE);
}
