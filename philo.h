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
	int				*conditional_forks;
	int				round_end;
	pthread_mutex_t	*forks;
	int				x;
	pthread_mutex_t	holder;
	pthread_mutex_t	holder2;
	pthread_mutex_t	holder3;
	pthread_mutex_t	holder4;
	int				death_flag1;
	pthread_t		*philos;
	int				flag2;
	int				nb_of_philos;
	struct s_philo	*philo;
	int				i;
	int				eat_rounds;
}	t_data;

typedef struct s_philo
{
	t_data 			*data;
	int				right_fork;
	int				left_fork;
	int				eat_flag2;
	int				philo_id;
	int				eat_time;
	int				sleep_time;
	int				flag;
	int				fork_flag;
	int				death_time;
	int				start_time;
	int				time_round;
	int				round;
	pthread_t		death;
	pthread_t		philos;
	int				past;
	int				time_diff;
	int				time_diff2;
	int				time_diff3;
	int				*eat_stop;
	int				j;
}		t_philo;

void	checkinput(char **argv, int i, int j);
int		pars(char **argv);
void	*launch(void *ptr);
void	eating(t_philo *philo);
void	dying_timer(t_philo *philo);
void	*dying_thread(void *ptr);
int		get_time(void);
int		ft_atoi(const char *str);
void	checkinput(char **argv, int i, int j);
void	ft_usleep2(t_philo *philo);
void	ft_usleep(t_philo *philo);
void	asleep(t_philo *philo);
void	think(t_philo *philo);
void	eat(t_philo *philo);
void	sleeping(t_philo *philo);
void	eating(t_philo *philo);
void	add_starter(t_philo *philo);
void	add_finisher(t_philo *philo);
void	init_values(char **argv, t_philo *philo, int i);
void	init_threads(t_data *data, t_philo *philo, char **argv);
void	init_for_data(t_data *data, int i, char **argv);
void	check_bg(t_data *data);
int		check_death_again(t_philo *philo);
void	print_death(t_data *data, int x);

#endif
