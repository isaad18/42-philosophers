#include"philo.h"

void	getvalues(char **argv, t_data *data, int argc)
{
	data->nb_philo = atoi(argv[1]);
	data->die_time = atoi(argv[2]);
	data->eat_time = atoi(argv[3]);
	data->sleep_time = atoi(argv[4]);
	data->nb_forks = atoi(argv[1]);
	if (argc == 6)
		data->rep_time = atoi(argv[5]);
	else
		data->rep_time = 0;
}

void	initvalues(t_data *data)
{
	int i;

	i = data->nb_philo;
	data->philo = malloc(sizeof(t_philo) * i);
	while (i <= 0)
	{
		data->philo[i].right_fork = (i + 1) % 5;
		data->philo[i].left_fork = i;
		data->philo[i].philo_id = i;
		data->philo[i].eat_rounds = 0;
	}
}