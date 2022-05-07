#include"philo.h"

int	get_time(void)
{
	struct timeval current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

int	get_timee(void)
{
	struct timeval current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

void	sleeping(t_philo *philo)
{
	philo->i = 0;
	philo->j = 0;
	printf("%s%d ms: philo %d is sleeping😴\n", green, (get_time() - philo->past), philo->philo_id + 1);
	usleep(philo->sleep_time * 1000);
	printf("%s%d ms: philo %d is thinking🤔\n", purple, (get_time() - philo->past), philo->philo_id + 1);
	philo->eat_stop[philo->philo_id] += 1;
	while (philo->eat_stop[philo->i] && philo->eat_rounds != 0)
	{
		if (philo->eat_stop[philo->i] == philo->eat_rounds)
			philo->j++;
		philo->i++;
	}
	if (philo->j == philo->nb_of_philos)
	{
		pthread_detach(philo->philos);
		pthread_detach(philo->death);
		exit(0);
	}
	if (philo->eat_stop[philo->philo_id] == philo->eat_rounds)
	{
		pthread_detach(philo->philos);
		pthread_detach(philo->death);
		while(1);
	}
	eating(philo);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->flag);
	printf("%s%d ms: philo %d took a fork🍴\n", cyan, (get_time() - philo->past), philo->philo_id + 1);
	printf("%s%d ms: philo %d took a fork🍴\n", cyan, (get_time() - philo->past), philo->philo_id + 1);
	printf("%s%d ms: philo %d is eating🍝\n", blue, (get_time() - philo->past), philo->philo_id + 1);
	usleep(philo->eat_time * 1000);
	philo->time_round = get_time();
	pthread_mutex_unlock(&philo->flag);
	pthread_mutex_unlock(&philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->forks[philo->right_fork]);
	sleeping(philo);
}

void	dying_timer(t_philo *philo)
{
	while (1)
	{
		usleep(10);
		pthread_mutex_lock(&philo->flag);
		if ((get_time() - philo->time_round) >= philo->death_time)
		{
			printf("%s%d ms: philo %d just died😵\n", red, (get_time() - philo->past), philo->philo_id + 1);
			exit(0);
		}
		pthread_mutex_unlock(&philo->flag);
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
	eating(philo);
	return (ptr);
}