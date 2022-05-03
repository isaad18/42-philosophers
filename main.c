#include"philo.h"

void    *test(void *ptr)
{
	printf("hi from threads\n");
	sleep(2);
	printf("lol\n");
	return (ptr);
}

int main(void)
{
	pthread_t		philo1;
	pthread_t		philo2;

	pthread_create(&philo1, NULL, &test, NULL);
	pthread_create(&philo2, NULL, &test, NULL);
	pthread_join(philo1, NULL);
	pthread_join(philo2, NULL);
	return (0);
}