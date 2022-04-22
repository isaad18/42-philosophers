RCS		= philo.c \
pars.c \

OBJS	= $(RCS:.c=.o)

NAME	= philo

CFLAGS	= -Wall -Werror -Wextra -g

$(NAME)	: $(OBJS)
		gcc $(CFLAGS) -o $(NAME) $(RCS)

all	: $(NAME)

clean :
		rm -f $(OBJS)

fclean : clean
		rm -f $(NAME)

re : fclean all