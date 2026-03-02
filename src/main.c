/* ################################################################################
# File:    main.c
# Author:  banjo-bytes
# Date:    2026-03-01
################################################################################ */

#include "philo.h"
#include <pthread.h>

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

/* Iteration 1: Forget timestamps, assume inputs correct, assume functions return successfully, only print to stdout the philosopher number and status*/

int	main(int argc, char **argv)
{
	t_shared	shared_vars;
	t_philo		*philos;
	pthread_t	*threads;

	if (argc < 5 || argc > 6) //TODO: Add || arg_check(argv))
		return (EXIT_FAILURE);
	if (init_resources(&shared_vars, &philos, arc, argv))
		return (EXIT_FAILURE);
	return (0);
}
