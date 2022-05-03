#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<unistd.h>
# include<strings.h>
# include<sys/time.h>
# include<stdlib.h>
# include<pthread.h>

# define black "\033[0;30m"
# define red "\033[0;31m"
# define green "\033[0;32m"
# define yellow "\033[0;33m"
# define blue "\033[0;34m"
# define purple "\033[0;35m"
# define cyan "\033[0;36m"
# define white "\033[0;37m"

typedef struct s_philo
{
	int				right_fork;
	int				left_fork;
	int				philo_id;
	int				eat_rounds;
	int				eat_time;
	int				sleep_time;
	int				flag;
	int				death_time;
	int				time_round;
	pthread_t		death;
	pthread_t		philos;
	pthread_mutex_t	*forks;
	int				past;
	int				time_diff;
}		t_philo;

void	checkinput(char **argv, int i, int j);
int		pars(char **argv);
void	*launch(void *ptr);
void	eating(t_philo *philo);

#endif