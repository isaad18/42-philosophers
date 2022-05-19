#include"philo.h"


int	get_time(void)
{
	struct timeval current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

void	ft_usleep2(t_philo *philo)
{
	philo->start_time = get_time();
	while (1)
	{
		usleep(50);
		if (get_time() - philo->start_time >= philo->eat_time)
			break;
	}
}

void	ft_usleep(t_philo *philo)
{
	philo->start_time = get_time();
	while (1)
	{
		usleep(50);
		if ((get_time() - philo->start_time) >= philo->sleep_time)
			break;
	}
}

void	dying_sleep(t_philo *philo)
{
	ft_usleep(philo);
}

void	asleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->holder2);
	// if (philo->data->death_flag1 == 0)
		printf("%s%d ms: philo %d is sleeping😴\n", green, (get_time() - philo->past), philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->holder2);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->holder2);
	// if (philo->data->death_flag1 == 0)
		printf("%s%d ms: philo %d is thinking🤔\n", purple, (get_time() - philo->past), philo->philo_id + 1);
	pthread_mutex_unlock(&philo->data->holder2);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->holder2);
	// if (philo->data->death_flag1 == 0)
	// {
		printf("%s%d ms: philo %d took a fork🍴\n", cyan, (get_time() - philo->past), philo->philo_id + 1);
		printf("%s%d ms: philo %d took a fork🍴\n", cyan, (get_time() - philo->past), philo->philo_id + 1);
		printf("%s%d ms: philo %d is eating🍝\n", blue, (get_time() - philo->past), philo->philo_id + 1);
	// }
	pthread_mutex_unlock(&philo->data->holder2);
}

void	sleeping(t_philo *philo)
{
	asleep(philo);
	ft_usleep(philo);
	think(philo);
	pthread_mutex_lock(&philo->data->holder);
	philo->round++;
	pthread_mutex_unlock(&philo->data->holder);
}

void	eating(t_philo *philo)
{
	while (philo->data->nb_of_philos == 1)
		dying_timer(philo);
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	}
	pthread_mutex_lock(&philo->data->holder3);
	philo->time_round = get_time();
	if (philo->data->death_flag1 == 0)
		eat(philo);
	pthread_mutex_unlock(&philo->data->holder3);
	ft_usleep2(philo);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);

}

void	dying_timer(t_philo *philo)
{
	if ((get_time() - philo->time_round) >= philo->death_time)
	{
		printf("%s%d ms: philo %d just died😵\n", red, (get_time() - philo->past), philo->philo_id + 1);
		philo->data->death_flag1 = 1;;
	}
}

void	*launch(void *ptr)
{
	t_philo	*philo;

	philo = (void *)ptr;
	philo->past = get_time();
	if ((philo->philo_id + 1) % 2 == 0)
		usleep(10000);
	philo->flag = 0;
	while (!philo->data->death_flag1)
	{
		eating(philo);
		pthread_mutex_lock(&philo->data->holder3);
		if (philo->data->death_flag1)
		{
			pthread_mutex_unlock(&philo->data->holder3);
			break;
		}
		pthread_mutex_unlock(&philo->data->holder3);
		sleeping(philo);
		if (philo->round == philo->data->eat_rounds)
			break;
	}
	pthread_mutex_lock(&philo->data->holder3);
	philo->eat_flag2 = 1;
	pthread_mutex_unlock(&philo->data->holder3);
	pthread_mutex_lock(&philo->data->holder);
	philo->data->i++;
	pthread_mutex_unlock(&philo->data->holder);
	return (0);
}
