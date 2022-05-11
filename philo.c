#include"philo.h"

int main(int argc, char **argv)
{
	int	i;
	int	j;
	t_data			data;
	int				round_end;
	t_philo			*philo;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	holder;
	pthread_mutex_t	holder2;
	pthread_mutex_t	holder3;
	pthread_mutex_t	holder4;
	pthread_mutex_t	holder5;

	philo = NULL;
	if (argc != 5 && argc != 6)
	{
		printf("%sError, invalid number of arguments!!\n", yellow);
		exit(1);
	}
	pars(argv);
	i = atoi(argv[1]);
	data.conditional_forks = malloc(sizeof(int) * i);
	philo = malloc(sizeof(t_philo) * i);
	philos = malloc(sizeof(pthread_t) * i);
	forks = malloc(sizeof(pthread_mutex_t) * i);
	i--;
	pthread_mutex_init(&holder, NULL);
	pthread_mutex_init(&holder2, NULL);
	pthread_mutex_init(&holder3, NULL);
	pthread_mutex_init(&holder4, NULL);
	pthread_mutex_init(&holder5, NULL);
	while (i >= 0)
	{
		data.conditional_forks[i] = 0;
		pthread_mutex_init(&forks[i], NULL);
		i--;
	}
	i = atoi(argv[1]) - 1;
	j = i + 1;
	while (i >= 0)
	{
		philos[i] = philo[i].philos;
		i--;
	}
	round_end = 0;
	i = atoi(argv[1]) - 1;
	while (i >= 0)
	{
		philo[i].round_end = round_end;
		philo[i].philoss = philos;
		philo[i].nb_of_philos = j;
		philo[i].right_fork = (i + 1) % (atoi(argv[1]));
		philo[i].left_fork = i;
		philo[i].philo_id = i;
		philo[i].eat_time = (atoi(argv[3]));
		philo[i].death_time = (atoi(argv[2]));
		philo[i].sleep_time = (atoi(argv[4]));
		philo[i].time_diff = 0;
		philo[i].round = 0;
		if (argv[5] != 0)
			philo[i].eat_rounds = (atoi(argv[5]));
		else
			philo[i].eat_rounds = 0;
		philo[i].data = &data;
		philo[i].holder = holder;
		philo[i].holder2 = holder2;
		philo[i].holder3 = holder3;
		philo[i].holder4 = holder4;
		philo[i].holder4 = holder5;
		philo[i].forks = forks;
		i--;
	}
	i = atoi(argv[1]) - 1;
	while (i >= 0)
	{
		pthread_create(&philo[i].philos, NULL, &launch, &philo[i]);
		// pthread_create(&philo[i].death, NULL, &dying_thread, &philo[i]);
		i--;
	}
	i = atoi(argv[1]) - 1;
	while (i >= 0)
	{
		pthread_join(philo[i].philos, NULL);
		// pthread_join(philo[i].death, NULL);
		i--;
	}
	return (0);
}
