#include"philo.h"

void	checkinput(char **argv, int i, int j)
{
	if ((argv[i][j] > 47 && argv[i][j] < 58) && argv[i]
            [j + 1] == '+')
	{
		printf("%sError, stupid input\n", red);
		exit(1);
	}
	if ((argv[i][j] == '+' && !(argv[i]
			[j + 1] > 47 && argv[i][j + 1] < 58)))
	{
		printf("%sError, stupid input\n", red);
		exit(1);
	}
	if (!((argv[i][j] > 47 && argv[i][j] < 58) || argv
		[i][j] == ' ' || argv[i][j] == '+'))
	{
		printf("%sError, stupid input\n", red);
		exit(1);
	}
}

int	pars(char **argv)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			checkinput(argv, i, j);
			j++;
		}
		i++;
	}
	return (0);
}

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
		usleep(100);
		if (get_time() - philo->start_time >= philo->eat_time)
			break;
	}
}

void	ft_usleep(t_philo *philo)
{
	philo->start_time = get_time();
	while (1)
	{
		usleep(100);
		if ((get_time() - philo->start_time) >= philo->sleep_time)
			break;
	}
}