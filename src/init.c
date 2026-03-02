/* ################################################################################
# File:    init.c
# Author:  banjo-bytes
# Date:    2026-03-02
################################################################################ */

static void	cleanup_resources(t_shared *shared_vars, int print_mtx, int forks, int *i)
{
	int	j;

	j = *i;
	if (print_mtx)
		pthread_mutex_destroy(&shared_vars->print_mtx);
	if (forks)
	{
		while (j > 0)
		{
			pthread_mutex_destroy(&shared_vars->forks[j]);
			j--;
		}
	}
}

static int	init_shared_vars(t_shared *shared_vars, int argc, char **argv)
{
	shared_vars->max_meals = 0;
	if (argc == 6)
		shared_vars->max_meals = atoi(argv[5]);
	shared_vars->num_philo = atoi(argv[1]);
	shared_vars->td = atoi(argv[2]);
	shared_vars->te = atoi(argv[3]);
	shared_vars->ts = atoi(argv[4]);
	if (pthread_mutex_init(&shared_vars->print_mtx, NULL))
	{
		cleanup_resources(shared_vars, 1, 0, NULL);
		return (1);
	}
	shared_vars->forks = (pthread_mutex_t *)malloc(shared_vars->num_philo * sizeof(pthread_mutex_t));
	if (shared_vars->forks == NULL)
		return (1);
	for (int i = 0; i < shared_vars->num_philo; i++)
	{
		if (pthread_mutex_init(&shared_vars->forks[i], NULL))
		{
			cleanup_resources(shared_vars, 0, 1, &i);
			return (1);
		}
	}
	return (0);
}

static t_philo	*init_philos(t_shared *shared_vars)
{
	t_philos	*philos;

	philos = (t_philo *)malloc(shared_vars->num_philos * sizeof(t_philo));
	if (philos == NULL)
	{
		cleanup_reosurces(shared_vars, 1, 1, NULL);
		return (NULL);
	}
	for (int i = 0; i < num_philo; i++)
	{
		philos[i].shared = shared_vars;
		philos[i].phil_id = i;
		philos[i].meals_eaten = 0;
	}
	return (philos);
}

int	init_resources(t_shared *shared_vars, t_philo **philos, int argc, char **argv)
{
	if (init_shared_vars(shared_vars, argc, argv))
		return (1);
	*philos = init_philos(shared_vars);
	if (*philos == NULL)
		return (1);
	return (0);
}
