/* ################################################################################
# File:    main.c
# Author:  banjo-bytes
# Date:    2026-03-01
################################################################################ */

#include "philo.h"
#include <stdlib.h>
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

typedef struct	s_shared {
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	*forks;
	int				num_philo;
	int				max_meals;
	int				td;
	int				te;
	int				ts;
}				t_shared;

typedef struct	s_philo {
	t_shared	*shared;
	int			phil_id;
	int			meals_eaten;
}				t_philo;

//TODO: Create a cleanup_resources fn

int	init_shared_vars(t_shared *shared_vars, int argc, char **argv)
{
	if (argc == 6)
		shared_vars->max_meals = atoi(argv[5]);
	else
		shared_vars->max_meals = 0;
	shared_vars->num_philo = atoi(argv[1]);
	shared_vars->td = atoi(argv[2]);
	shared_vars->te = atoi(argv[3]);
	shared_vars->ts = atoi(argv[4]);
	pthread_mutex_init(&shared_vars->print_mtx, NULL);
	shared_vars->forks = (pthread_mutex_t *)malloc(shared_vars->num_philo * sizeof(pthread_mutex_t));
	if (shared_vars->forks == NULL)
		return (1);
	for (int i = 0; i < shared_vars->num_philo; i++)
		pthread_mutex_init(&shared_vars->forks[i], NULL);
	return (0);
}

int	init_philos(t_philo *philos, t_shared *shared_vars)
{
	philos = (t_philo *)malloc(shared_vars->num_philos * sizeof(t_philo));
	if (philos == NULL)
	{	
		cleanup_reosurces(NULL, shared_vars);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_shared	shared_vars;
	t_philo		*philos;
	pthread_t	*threads;

	if (argc < 5 || argc > 6) //TODO: Add || arg_check(argv))
		return (EXIT_FAILURE);
	if (init_shared_vars(&shared_vars, argc, argv) || init_philos(philos, &shared_vars))
		return (EXIT_FAILURE);	
	return (0);
}
