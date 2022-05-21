#include"philo.h"

int	check_death_again(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->holder3);
	if (philo->data->death_flag1)
	{
		pthread_mutex_unlock(&philo->data->holder3);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->holder3);
	return (0);
}

void	print_death(t_data *data, int x)
{
	pthread_mutex_lock(&data->holder2);
	printf("%s%d ms: philo %d just died😵\n", red,
		(get_time() - data->philo[x].past), data->philo[x].philo_id + 1);
	pthread_mutex_unlock(&data->holder2);
}
