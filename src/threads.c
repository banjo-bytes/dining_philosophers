/* ################################################################################
# File:    threads.c
# Author:  banjo-bytes
# Date:    2026-03-02
################################################################################ */

#include "philo.h"

int	create_threads(pthread_t *threads, t_philo *philos)
{
	for (int i = 0; i < philos->shared_vars.num_philo; i++)
	{
		if (pthread_create(&threads[i], NULL, &thread_handler(), &philos[i]))
		{
			cleanup_thread_resources();
			return (1);
		}
	}
	return (0);
}

int	wait_threads(pthread_t *threads, t_shared *shared_vars)
{
	for (int i = 0; i < shared_vars->num_philo; i++)
		pthread_join(threads[i], NULL);
}
