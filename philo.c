#include"philo.h"

int main(int argc, char **argv)
{
	int	i;
	int	j;
	int	n;
	t_data			data;
	int				round_end;
	t_philo			*philo;
	pthread_t		*philos;

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
	data.forks = malloc(sizeof(pthread_mutex_t) * i);
	i--;
	pthread_mutex_init(&data.holder, NULL);
	pthread_mutex_init(&data.holder2, NULL);
	pthread_mutex_init(&data.holder3, NULL);
	pthread_mutex_init(&data.holder4, NULL);
	pthread_mutex_init(&data.holder5, NULL);
	while (i >= 0)
	{
		data.conditional_forks[i] = 0;
		pthread_mutex_init(&data.forks[i], NULL);
		i--;
	}
	data.round_end = 0;
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
		i--;
	}
	i = atoi(argv[1]) - 1;
	j = i / 10;
	n = i - j;
	while(n)
	{
		while (i >= 0)
		{
			pthread_create(&philo[i].philos, NULL, &launch, &philo[i]);
			// pthread_create(&philo[i].death, NULL, &dying_thread, &philo[i]);
			i--;
		}
		n -= j;
	}
	i = atoi(argv[1]) - 1;
	j = i / 10;
	n = i - j;
	while(n)
	{
		while (i >= n)
		{
			pthread_join(philo[i].philos, NULL);
			// pthread_join(philo[i].death, NULL);
			i--;
		}
		n -= j;
	}
	return (0);
}
