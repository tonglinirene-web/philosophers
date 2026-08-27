#include "philo.h"

static int	is_digit_string(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (FALSE);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	ft_atol_positive(char *str, long *result)
{
	long	value;
	int		i;

	if (is_digit_string(str) == FALSE)
		return (FALSE);
	value = 0;
	i = 0;
	while (str[i])
	{
		value = value * 10 + (str[i] - '0');
		if (value > INT_MAX)
			return (FALSE);
		i++;
	}
	if (value <= 0)
		return (FALSE);
	*result = value;
	return (TRUE);
}

static int	parse_required(char **argv, t_table *table)
{
	long	value;

	if (ft_atol_positive(argv[1], &value) == FALSE)
		return (printf("Error: invalid number_of_philosophers\n"), FALSE);
	table->philo_count = (int)value;
	if (ft_atol_positive(argv[2], &table->time_to_die) == FALSE)
		return (printf("Error: invalid time_to_die\n"), FALSE);
	if (ft_atol_positive(argv[3], &table->time_to_eat) == FALSE)
		return (printf("Error: invalid time_to_eat\n"), FALSE);
	if (ft_atol_positive(argv[4], &table->time_to_sleep) == FALSE)
		return (printf("Error: invalid time_to_sleep\n"), FALSE);
	return (TRUE);
}

int	parse_args(int argc, char **argv, t_table *table)
{
	long	value;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (FALSE);
	}
	if (parse_required(argv, table) == FALSE)
		return (FALSE);
	table->must_eat = -1;
	if (argc == 6)
	{
		if (ft_atol_positive(argv[5], &value) == FALSE)
			return (printf("Error: invalid meals count\n"), FALSE);
		table->must_eat = (int)value;
	}
	return (TRUE);
}
