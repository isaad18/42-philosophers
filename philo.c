#include"philo.h"

int main(int argc, char **argv)
{
	int	i;
	int	j;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				*eat_stop;

	philo = NULL;
	if (argc != 5 && argc != 6)
	{
		printf("%sError, invalid number of arguments!!\n", yellow);
		exit(1);
	}
	pars(argv);
	i = atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * i);
	forks = malloc(sizeof(pthread_mutex_t) * i);
	eat_stop = malloc(sizeof(int) * i);
	i--;
	while (i >= 0)
	{
		eat_stop[i] = 0;
		// printf("%d\n", eat_stop[i]);
		pthread_mutex_init(&forks[i], NULL);
		i--;
	}
	i = atoi(argv[1]) - 1;
	j = i + 1;
	while (i >= 0)
	{
		philo[i].nb_of_philos = j;
		philo[i].eat_stop = eat_stop;
		philo[i].forks = forks;
		philo[i].right_fork = (i + 1) % (atoi(argv[1]));
		philo[i].left_fork = i;
		philo[i].philo_id = i;
		philo[i].flag = 0;
		philo[i].eat_time = (atoi(argv[3]));
		philo[i].death_time = (atoi(argv[2]));
		philo[i].sleep_time = (atoi(argv[4]));
		philo[i].time_diff = 0;
		if (argv[5] != 0)
			philo[i].eat_rounds = (atoi(argv[5]));
		else
			philo[i].eat_rounds = 0;
		i--;
	}
	i = atoi(argv[1]) - 1;
	while (i >= 0)
	{
		pthread_create(&philo[i].philos, NULL, &launch, &philo[i]);
		pthread_create(&philo[i].death, NULL, &dying_thread, &philo[i]);
		i--;
	}
	i = atoi(argv[1]) - 1;
	while (i >= 0)
	{
		pthread_join(philo[i].philos, NULL);
		pthread_join(philo[i].death, NULL);
		i--;
	}
	return (0);
}
