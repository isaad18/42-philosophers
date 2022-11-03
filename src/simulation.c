#include"../includes/philo.h"

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

void	add_starter(t_philo *philo)
{
	philo->past = get_time();
	if ((philo->philo_id + 1) % 2 == 0)
		usleep(10000);
	philo->flag = 0;
}

void	add_finisher(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->holder3);
	philo->eat_flag2 = 1;
	pthread_mutex_unlock(&philo->data->holder3);
	pthread_mutex_lock(&philo->data->holder);
	philo->data->i++;
	pthread_mutex_unlock(&philo->data->holder);
}

void	*launch(void *ptr)
{
	t_philo	*philo;
	int		death;
	int		x;

	philo = (void *)ptr;
	add_starter(philo);
	pthread_mutex_lock(&philo->data->holder3);
	death = philo->data->death_flag1;
	pthread_mutex_unlock(&philo->data->holder3);
	while (!death)
	{
		eating(philo);
		x = check_death_again(philo);
		if (x == 1)
			break ;
		sleeping(philo);
		if (philo->round == philo->data->eat_rounds)
			break ;
		pthread_mutex_lock(&philo->data->holder3);
		death = philo->data->death_flag1;
		pthread_mutex_unlock(&philo->data->holder3);
	}
	add_finisher(philo);
	return (0);
}

// void	eating(t_philo *philo)
// {
	// pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	// if (philo->data->conditional_forks[philo->right_fork] == 1)
	// 	philo->data->conditional_forks[philo->right_fork] = 0;
	// pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	// pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	// if (philo->data->conditional_forks[philo->left_fork] == 1)
	// 	philo->data->conditional_forks[philo->left_fork] = 0;
	// pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
// 	philo->fork_flag = 0;
// 	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
// 	if (philo->data->conditional_forks[philo->right_fork] == 0)
// 	{
// 		pthread_mutex_lock(&philo->data->holder3);
// 		if (philo->data->death_flag1 == 0)
// 		{
// 			pthread_mutex_lock(&philo->data->holder2);
// 			printf("%s%d ms: philo %d took a fork🍴\n", cyan
		// , (get_time() - philo->past), philo->philo_id + 1);
// 			pthread_mutex_unlock(&philo->data->holder2);
// 		}
// 		philo->fork_flag = 1;
// 		pthread_mutex_unlock(&philo->data->holder3);
// 		philo->data->conditional_forks[philo->right_fork] = 1;
// 	}
// 	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
// 	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
// 	if (philo->data->conditional_forks[philo->left_fork] == 0)
// 	{
// 		pthread_mutex_lock(&philo->data->holder3);
// 		if (philo->data->death_flag1 == 0)
// 		{
// 			pthread_mutex_lock(&philo->data->holder2);
// 			printf("%s%d ms: philo %d took a fork🍴\n",
		// cyan, (get_time() - philo->past), philo->philo_id + 1);
// 			pthread_mutex_unlock(&philo->data->holder2);
// 		}
// 		philo->fork_flag = 2;
// 		pthread_mutex_unlock(&philo->data->holder3);
// 		philo->data->conditional_forks[philo->left_fork] = 1;
// 	}
// 	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
// 	if (philo->fork_flag == 2)
// 	{
// 		philo->time_round = get_time();
// 		pthread_mutex_lock(&philo->data->holder2);
// 		printf("%s%d ms: philo %d is eating🍝\n", blue,
		// (get_time() - philo->past), philo->philo_id + 1);
// 		pthread_mutex_unlock(&philo->data->holder2);
// 		ft_usleep2(philo);
// 		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
// 		philo->data->conditional_forks[philo->right_fork] = 0;
// 		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
// 		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
// 		philo->data->conditional_forks[philo->left_fork] = 0;
// 		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
// 	}
// }
