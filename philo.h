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
	struct s_data	*data;
	pthread_t		philo;
}		t_philo;

typedef struct s_data
{
	long int	nb_philo;
	long int	die_time;
	long int	rep_time;
	long int	eat_time;
	long int	sleep_time;
	long int	nb_forks;
	long int	nb_of_cycles;
	t_philo	*philo;
}		t_data;

void	checkinput(char **argv, int i, int j);
int		jawaker(char **argv);
void	getvalues(char **argv, t_data *data, int argc);
void	initvalues(t_data *data);

#endif