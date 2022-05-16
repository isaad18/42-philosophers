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
		if (get_time() - philo->start_time >= philo->eat_time)
			break ;
	}
}

void	ft_usleep(t_philo *philo)
{
	int	i;

	i = 0;
	philo->start_time = get_time();
	while (1)
	{
		if ((get_time() - philo->start_time) >= philo->sleep_time)
			break ;
		if ((get_time() - philo->time_round) >= philo->death_time)
		{
			printf("%s%d ms: philo %d just died😵\n", red, (get_time() - philo->past), philo->philo_id + 1);
			while (i < philo->data->nb_of_philos)
			{
				pthread_detach(philo->data->philos[i]);
				i++;
			}
			exit(0);
		}
	}
}

void	dying_sleep(t_philo *philo)
{
	ft_usleep(philo);
	// dying_timer(philo);
}

void	mutex_diff5(t_philo *philo)
{
	philo->time_diff2 = get_time();
	pthread_mutex_lock(&philo->data->holder5);
	philo->time_diff3 = get_time() - philo->time_diff2;
	philo->time_round += philo->time_diff3;
}

void	asleep(t_philo *philo)
{
	printf("%s%d ms: philo %d is sleeping😴\n", green, (get_time() - philo->past), philo->philo_id + 1);
}

void	think(t_philo *philo)
{
		printf("%s%d ms: philo %d is thinking🤔\n", purple, (get_time() - philo->past), philo->philo_id + 1);
}

void	eat(t_philo *philo)
{
	printf("%s%d ms: philo %d took a fork🍴\n", cyan, (get_time() - philo->past), philo->philo_id + 1);
	printf("%s%d ms: philo %d took a fork🍴\n", cyan, (get_time() - philo->past), philo->philo_id + 1);
	printf("%s%d ms: philo %d is eating🍝\n", blue, (get_time() - philo->past), philo->philo_id + 1);
}

void	sleeping(t_philo *philo)
{
	dying_timer(philo);
	if (philo->flag == 1)
	{
		// mutex_diff5(philo);
		// pthread_mutex_lock(&philo->data->holder5);
		asleep(philo);
		// pthread_mutex_unlock(&philo->data->holder5);
		dying_sleep(philo);
		// mutex_diff5(philo);
		// pthread_mutex_lock(&philo->data->holder5);
		think(philo);
		// pthread_mutex_unlock(&philo->data->holder5);
		// pthread_mutex_lock(&philo->data->holder);
		philo->i = 0;
		philo->j = 0;
		philo->round++;
		if (philo->round == philo->eat_rounds)
		{
			philo->data->round_end++;
			if (philo->data->round_end == philo->data->nb_of_philos)
			{
				pthread_detach(philo->philos);
				free(philo->data->philos);
				while (philo->i < philo->data->nb_of_philos)
				{
					pthread_mutex_destroy(&philo->data->forks[philo->i]);
					philo->i++;
				}
				exit(0);
			}
			else
			{
				pthread_detach(philo->philos);
				while (1);
			}
		}
		philo->flag = 0;
	}
}

void	eating(t_philo *philo)
{
	dying_timer(philo);
	philo->flag = 0;
	while (philo->data->nb_of_philos == 1)
		dying_timer(philo);
	// if (philo->philo_id % 2 == 0)
	// {
	// }
	// else
	// {
		// pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		// pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	// }
	// pthread_mutex_lock(&philo->data->holder);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	if (philo->data->conditional_forks[philo->left_fork] == 0 && philo->data->conditional_forks[philo->right_fork] == 0)
	{
		philo->data->conditional_forks[philo->right_fork] = 1;
		philo->data->conditional_forks[philo->left_fork] = 1;
		philo->flag = 1;
	}
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		// pthread_mutex_lock(&philo->data->holder2);
		// pthread_mutex_unlock(&philo->data->holder);
		// pthread_mutex_unlock(&philo->data->holder2);
	if (philo->flag == 1)
	{
		// usleep(philo->eat_time * 1000);
		// pthread_mutex_lock(&philo->data->holder4);
		// mutex_diff4(philo);
		eat(philo);
		// pthread_mutex_unlock(&philo->data->holder4);
		philo->time_round = get_time();
		ft_usleep2(philo);
		pthread_mutex_lock(&philo->data->holder3);
		philo->data->conditional_forks[philo->left_fork] = 0;
		philo->data->conditional_forks[philo->right_fork] = 0;
		pthread_mutex_unlock(&philo->data->holder3);
	}
}

void	dying_timer(t_philo *philo)
{
	int	i;

	i = 0;
	if ((get_time() - philo->time_round) >= philo->death_time)
	{
		while (i < philo->data->nb_of_philos)
		{
			pthread_detach(philo->data->philos[i]);
			i++;
		}
		printf("%s%d ms: philo %d just died😵\n", red, (get_time() - philo->past), philo->philo_id + 1);
		exit(0);
	}
}

void	*dying_thread(void *ptr)
{
	t_philo	*philo;

	philo = (void *)ptr;
	dying_timer(philo);
	return (0);
}

void	*launch(void *ptr)
{
	t_philo	*philo;

	philo = (void *)ptr;
	philo->past = get_time();
	philo->time_round = get_time();
	if (philo->philo_id % 2 == 0)
		usleep(100);
	philo->flag = 0;
	while (1)
	{
		eating(philo);
		sleeping(philo);
	}
	return (ptr);
}
