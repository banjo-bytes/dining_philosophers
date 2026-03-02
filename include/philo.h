/* ################################################################################
# File:    philo.h
# Author:  banjo-bytes
# Date:    2026-03-02
################################################################################ */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <pthread.h>

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

int		init_resources(t_shared *shared_vars, t_philo **philos, int argc, char **argv);
void	*thread_handler(void *philo);

#endif
