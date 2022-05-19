#include"philo.h"

void	check_bg(t_data *data)
{
	int	x;

	while (data->death_flag1 == 0)
	{
		x = 0;
		while (x < data->nb_of_philos && data->death_flag1 == 0)
		{
			pthread_mutex_lock(&data->holder3);
			if ((get_time() - data->philo[x].time_round) > data->philo[x].death_time && data->philo[x].eat_flag2 == 0)
			{
				pthread_mutex_lock(&data->holder2);
				printf("%s%d ms: philo %d just died😵\n", red, (get_time() - data->philo[x].past), data->philo[x].philo_id + 1);
				pthread_mutex_unlock(&data->holder2);
				data->death_flag1 = 1;
			}
			pthread_mutex_unlock(&data->holder3);
			usleep(100);
			x++;
		}
		if (data->death_flag1 == 1)
		{
			break;
		}
		pthread_mutex_lock(&data->holder);
		if (data->i == data->nb_of_philos)
		{
			pthread_mutex_unlock(&data->holder);
			break;
		}
		pthread_mutex_unlock(&data->holder);
	}
}

int main(int argc, char **argv)
{
	int	i;
	int	j;
	t_data			data;
	t_philo			*philo;

	philo = NULL;
	if (argc != 5 && argc != 6)
	{
		printf("%sError, invalid number of arguments!!\n", yellow);
		return (1);
	}
	pars(argv);
	i = atoi(argv[1]);
	data.conditional_forks = malloc(sizeof(int) * i);
	philo = malloc(sizeof(t_philo) * i);
	data.philos = malloc(sizeof(pthread_t) * i);
	data.forks = malloc(sizeof(pthread_mutex_t) * i);
	data.philo = philo;
	i--;
	data.i = 0;
	while (i >= 0)
	{
		data.conditional_forks[i] = 0;
		pthread_mutex_init(&data.forks[i], NULL);
		i--;
	}
	pthread_mutex_init(&data.holder2, NULL);
	pthread_mutex_init(&data.holder3, NULL);
	pthread_mutex_init(&data.holder, NULL);
	data.round_end = 0;
	data.flag2 = 1;
	data.death_flag1 = 0;
	i = atoi(argv[1]) - 1;
	j = i + 1;
	data.nb_of_philos = j;
	while (i >= 0)
	{
		data.philos[i] = philo[i].philos;
		i--;
	}
	if (argv[5] != 0)
		data.eat_rounds = (atoi(argv[5]));
	else
		data.eat_rounds = 0;
	i = atoi(argv[1]) - 1;
	while (i >= 0)
	{
		philo[i].right_fork = (i + 1) % (atoi(argv[1]));
		philo[i].left_fork = i;
		philo[i].philo_id = i;
		philo[i].eat_time = (atoi(argv[3]));
		philo[i].death_time = (atoi(argv[2]));
		philo[i].sleep_time = (atoi(argv[4]));
		philo[i].time_diff = 0;
		philo[i].round = 0;
		philo[i].time_round = get_time();
		philo[i].data = &data;
		data.philo[i] = philo[i];
		philo[i].eat_flag2 = 0;
		i--;
	}
	i = atoi(argv[1]) - 1;
	while (i >= 0)
	{
		philo[i].time_round = get_time();
		pthread_create(&philo[i].philos, NULL, &launch, &philo[i]);
		i--;
	}
	i = atoi(argv[1]) - 1;
	check_bg(&data);
	i = atoi(argv[1]) - 1;
	while (i >= 0)
	{
		pthread_join(philo[i].philos, NULL);
		i--;
	}
	return (0);
}
