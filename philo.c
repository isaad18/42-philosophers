#include"philo.h"

int main(int argc, char **argv)
{
	t_data			data;

	if (argc != 5 && argc != 6)
	{
		printf("%sError, invalid number of arguments!!\n", yellow);
		exit(1);
	}
	data.nb_of_cycles = 0;
	jawaker(argv);
	getvalues(argv, &data, argc);
	return (0);
}
