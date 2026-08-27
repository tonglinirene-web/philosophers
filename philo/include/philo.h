#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				philo_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	int				stop;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	fork_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	state_lock;
	t_philo			*philos;
}	t_table;

int		parse_args(int argc, char **argv, t_table *table);
int		init_table(t_table *table);
int		start_simulation(t_table *table);
void	cleanup_table(t_table *table);

long	get_time_ms(void);
long	elapsed_time(t_table *table);
void	smart_sleep(t_table *table, long duration);

void	*routine(void *arg);
void	monitor(t_table *table);
void	print_status(t_philo *philo, char *status);

int		get_stop(t_table *table);
void	set_stop(t_table *table, int value);

#endif
