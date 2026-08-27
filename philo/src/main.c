#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (parse_args(argc, argv, &table) == FALSE)
		return (1);
	if (init_table(&table) == FALSE)
		return (1);
	if (start_simulation(&table) == FALSE)
	{
		cleanup_table(&table);
		return (1);
	}
	cleanup_table(&table);
	return (0);
}
