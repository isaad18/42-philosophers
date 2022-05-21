#include"philo.h"

void	asleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->holder2);
	printf("%s%d ms: philo %d is sleeping😴\n", green, (get_time() - philo->past), philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->holder2);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->holder2);
	printf("%s%d ms: philo %d is thinking🤔\n", purple, (get_time() - philo->past), philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->holder2);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->holder2);
	printf("%s%d ms: philo %d took a fork🍴\n", cyan, (get_time() - philo->past), philo->philo_id + 1);
	printf("%s%d ms: philo %d took a fork🍴\n", cyan, (get_time() - philo->past), philo->philo_id + 1);
	printf("%s%d ms: philo %d is eating🍝\n", blue, (get_time() - philo->past), philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->holder2);
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
		philo[i].fork_flag = 0;
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
	data->conditional_forks = malloc(sizeof(int) * i);
	data->philos = malloc(sizeof(pthread_t) * i);
	data->forks = malloc(sizeof(pthread_mutex_t) * i);
	data->nb_of_philos = i;
	i--;
	data->i = 0;
	while (i >= 0)
	{
		data->conditional_forks[i] = 0;
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