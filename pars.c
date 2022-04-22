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

int	jawaker(char **argv)
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