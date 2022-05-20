#include"philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	size_t	res;
	int		j;

	j = 1;
	i = 0;
	res = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * j);
}

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
			break;
		pthread_mutex_lock(&data->holder);
		if (data->i == data->nb_of_philos)
		{
			pthread_mutex_unlock(&data->holder);
			break;
		}
		pthread_mutex_unlock(&data->holder);
	}
}

void	init_values(char **argv, t_philo *philo, int i)
{
	while (i >= 0)
	{
		philo[i].right_fork = (i + 1) % (ft_atoi(argv[1]));
		philo[i].left_fork = i;
		philo[i].philo_id = i;
		philo[i].eat_time = (ft_atoi(argv[3]));
		philo[i].death_time = (ft_atoi(argv[2]));
		philo[i].sleep_time = (ft_atoi(argv[4]));
		philo[i].time_diff = 0;
		philo[i].round = 0;
		philo[i].time_round = get_time();
		philo[i].eat_flag2 = 0;
		i--;
	}
}

void	init_threads(t_data *data, t_philo *philo, char **argv)
{
	int	i;

	i = ft_atoi(argv[1]) - 1;
	while (i >= 0)
	{
		data->philos[i] = philo[i].philos;
		i--;
	}
	i = ft_atoi(argv[1]) - 1;
	init_values(argv, philo, i);
	while (i >= 0)
	{
		data->philo[i] = philo[i];
		philo[i].data = data;
		philo[i].time_round = get_time();
		pthread_create(&philo[i].philos, NULL, &launch, &philo[i]);
		i--;
	}
	i = ft_atoi(argv[1]) - 1;
	check_bg(data);
	i = ft_atoi(argv[1]) - 1;
	while (i >= 0)
	{
		pthread_join(philo[i].philos, NULL);
		i--;
	}
}

void	init_for_data(t_data *data, int i, char **argv)
{
	data->philos = malloc(sizeof(pthread_t) * i);
	data->forks = malloc(sizeof(pthread_mutex_t) * i);
	data->nb_of_philos = i;
	i--;
	data->i = 0;
	while (i >= 0)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i--;
	}
	pthread_mutex_init(&data->holder2, NULL);
	pthread_mutex_init(&data->holder3, NULL);
	pthread_mutex_init(&data->holder, NULL);
	data->round_end = 0;
	data->flag2 = 1;
	data->death_flag1 = 0;
	if (argv[5] != 0)
		data->eat_rounds = (ft_atoi(argv[5]));
	else
		data->eat_rounds = 0;
}

int main(int argc, char **argv)
{
	int	i;
	t_data			data;
	t_philo			*philo;

	philo = NULL;
	if (argc != 5 && argc != 6)
	{
		printf("%sError, invalid number of arguments!!\n", yellow);
		return (1);
	}
	pars(argv);
	i = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * i);
	data.philo = philo;
	init_for_data(&data, i, argv);
	init_threads(&data, philo, argv);
	free(data.philos);
	free(data.forks);
	free(philo);
	return (0);
}
