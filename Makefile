RCS		= philo.c \
pars.c \
simulation.c

OBJS	= $(RCS:.c=.o)

NAME	= philo

CFLAGS	= -Wall -Werror -Wextra

$(NAME)	: $(OBJS)
		@gcc $(CFLAGS)  $(RCS) -lpthread -o $(NAME)

all	: $(NAME)

clean :
		rm -f $(OBJS)

fclean : clean
		rm -f $(NAME)

re : fclean all