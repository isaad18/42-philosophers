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

int	check_eat(t_data *data)
{
	pthread_mutex_lock(&data->holder);
	if (data->i == data->nb_of_philos)
	{
		pthread_mutex_unlock(&data->holder);
		return (1);
	}
	pthread_mutex_unlock(&data->holder);
	return (0);
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
				print_death(data, x);
				data->death_flag1 = 1;
			}
			pthread_mutex_unlock(&data->holder3);
			usleep(100);
			x++;
		}
		if (data->death_flag1 == 1)
			break ;
		x = check_eat(data);
		if (x == 1)
			break ;
	}
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
	free(data.conditional_forks);
	free(data.philos);
	free(data.forks);
	free(philo);
	return (0);
}
