/* ################################################################################
# File:    main.c
# Author:  banjo-bytes
# Date:    2026-03-01
################################################################################ */

#include "philo.h"

/*	Usage: ./phil N td te ts [Nm]
	N - Number of philosophers
	td - time to die (ms)
	te - time to eat (ms)
	ts - time to sleep (ms)
	[Nm] - number of meals before sim stops [optional]
*/

/* Create a thread:
Printing status to stdout => Each philosopher needs access to global time elapsed timestamp, its own ID/no., left+right fork, mutex lock for the stdout printing buffer
Simulation tracking => Each philosopher needs to track number of meals eaten and Nm (if provided), must know td, te, ts
*/

static int	create_threads(pthread_t **threads, t_shared *shared_vars, t_philo *philos)
{
	*threads = (pthread_t *)malloc(shared_vars->num_philo * sizeof(pthread_t));
	if (*threads == NULL)
		return (1);
	for (int i = 0; i < philos->shared_vars.num_philo; i++)
	{
		if (pthread_create(*threads + i, NULL, &thread_handler(), &philos[i]))
		{
			//TODO: cleanup_thread_resources();
			return (1);
		}
	}
	return (0);
}

static int	wait_threads(pthread_t *threads, t_shared_vars *shared_vars)
{
	for (int i = 0; i < shared_vars->num_philo; i++)
		pthread_join(threads[i], NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_shared	shared_vars;
	t_philo		*philos;
	pthread_t	*threads;

	if (argc < 5 || argc > 6) //TODO: Add || arg_check(argv))
		return (EXIT_FAILURE);
	if (init_resources(&shared_vars, &philos, arc, argv))
		return (EXIT_FAILURE);
	create_threads(&threads, &shared_vars, philos); //TODO: Add error handling
	wait_threads(threads, &shared_vars);
	return (0);
}
