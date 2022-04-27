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
	data->all_ph = malloc(data->nb_philo);
	data->ate_or_no = malloc((data->nb_philo) * sizeof(int));
}

void	eating(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->nb_philo)
	{
		if (data->ate_or_no[i] == data->nb_of_cycles)
		{
			data->ate_or_no[i] += 1;
		}
		i++;
	}
	i = 0;
	while ((i + 1) < data->nb_philo)
	{
		if (data->ate_or_no[i] == data->ate_or_no[i + 1])
			j++;
		i++;
	}
	if (j == i)
		data->nb_of_cycles++;
}

void*	testt()
{
	if (1)
	{
		printf("%sthread is working\n", cyan);
		printf("%s2nd msg\n", yellow);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_data			data;
	int				j;
	int		i;
	pthread_t	*test;
	test = NULL;

	i = 0;
	j = 0;
	test = malloc(5 * sizeof(pthread_t));
	while (i < 5)
	{
		pthread_create(&test[i], NULL, &testt, NULL);
		pthread_join(test[i], NULL);
		i++;
	}
	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("%sError, invalid number of arguments!!\n", yellow);
		exit(1);
	}
	data.nb_of_cycles = 0;
	j = jawaker(argv);
	getvalues(argv, &data, argc);
	return (0);
}
