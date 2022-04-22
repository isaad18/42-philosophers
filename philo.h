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

typedef struct s_data
{
	int	nb_philo;
	int	die_time;
	int	eat_time;
	int	rep_time;
	int	sleep_time;
	int	nb_forks;
	int	nb_of_cycles;
	int	*all_ph;
	int	*ate_or_no;
}		t_data;

void	checkinput(char **argv, int i, int j);
int		jawaker(char **argv);

#endif