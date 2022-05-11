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
		if (get_time() - philo->start_time >= philo->sleep_time)
			break ;
		if ((get_time() - philo->time_round) >= philo->death_time)
		{
			printf("%s%d ms: philo %d just died😵\n", red, (get_time() - philo->past), philo->philo_id + 1);
			while (i < philo->nb_of_philos)
			{
				pthread_detach(philo->philoss[i]);
				i++;
			}
			exit(0);
		}
	}
}

void	dying_sleep(t_philo *philo)
{
	ft_usleep(philo);
	dying_timer(philo);
}

void	sleeping(t_philo *philo)
{
	if (philo->flag == 1)
	{
		philo->i = 0;
		philo->j = 0;
		pthread_mutex_lock(&philo->holder);
		printf("%s%d ms: philo %d is sleeping😴\n", green, (get_time() - philo->past), philo->philo_id + 1);
		pthread_mutex_unlock(&philo->holder);
		dying_sleep(philo);
		pthread_mutex_lock(&philo->holder);
		printf("%s%d ms: philo %d is thinking🤔\n", purple, (get_time() - philo->past), philo->philo_id + 1);
		pthread_mutex_unlock(&philo->holder);
		// philo->round++;
		// if (philo->round == philo->eat_rounds)
		// {
		// 	philo->data->round_end++;
		// 	pthread_mutex_lock(&philo->holder3);
		// 	if (philo->data->round_end == philo->nb_of_philos)
		// 	{
		// 		pthread_mutex_unlock(&philo->holder3);
		// 		pthread_detach(philo->philos);
		// 		pthread_detach(*philo->philoss);
		// 		while (philo->i < philo->nb_of_philos)
		// 		{
		// 			pthread_mutex_destroy(&philo->forks[philo->i]);
		// 			philo->i++;
		// 		}
		// 		exit(0);
		// 	}
		// 	else
		// 	{
		// 		pthread_mutex_unlock(&philo->holder3);
		// 		pthread_detach(philo->philos);
		// 		while (1);
		// 	}
		// 	pthread_mutex_unlock(&philo->holder3);
		// }
	}
	philo->flag = 0;
}

void	eating(t_philo *philo)
{
	philo->flag = 0;
	while (philo->nb_of_philos == 1)
		dying_timer(philo);
	dying_timer(philo);
	pthread_mutex_lock(&philo->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->holder2);
	if (philo->data->conditional_forks[philo->right_fork] == 0 && philo->data->conditional_forks[philo->left_fork] == 0)
	{
		printf("%s%d ms: philo %d took a fork🍴\n", cyan, (get_time() - philo->past), philo->philo_id + 1);
		printf("%s%d ms: philo %d took a fork🍴\n", cyan, (get_time() - philo->past), philo->philo_id + 1);
		printf("%s%d ms: philo %d is eating🍝\n", blue, (get_time() - philo->past), philo->philo_id + 1);
		philo->data->conditional_forks[philo->right_fork] = 1;
		philo->data->conditional_forks[philo->left_fork] = 1;
		philo->time_round = get_time();
		philo->flag = 1;
	}
	pthread_mutex_unlock(&philo->holder2);
	pthread_mutex_unlock(&philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->holder4);
	if (philo->flag == 1)
	{
		// ft_usleep2(philo);
		usleep(philo->eat_time * 1000);
		philo->data->conditional_forks[philo->left_fork] = 0;
		philo->data->conditional_forks[philo->right_fork] = 0;
	}
	pthread_mutex_unlock(&philo->holder4);
}

void	dying_timer(t_philo *philo)
{
	int	i;

	i = 0;
	// pthread_mutex_lock(&philo->holder);
	if ((get_time() - philo->time_round) >= philo->death_time)
	{
		while (i < philo->nb_of_philos)
		{
			pthread_detach(philo->philoss[i]);
			i++;
		}
		printf("%s%d ms: philo %d just died😵\n", red, (get_time() - philo->past), philo->philo_id + 1);
		exit(0);
	}
	// pthread_mutex_unlock(&philo->holder);
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
	while (1)
	{
		eating(philo);
		sleeping(philo);
	}
	return (ptr);
}