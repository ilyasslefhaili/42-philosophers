NAME = philo_bonus

PHILO_A = philo_bonus.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = philo_bonus.c\
		atoi.c\
		philo_bonus_util.c

OBJS = $(subst .c,.o, $(SRCS))

all : $(NAME)

$(NAME) : $(PHILO_A)
		$(CC) $(CFLAGS) $(PHILO_A) -o $(NAME)

$(PHILO_A) : $(OBJS)
		$(CC) $(CFLAGS) -c $(SRCS)
		ar -rc $(PHILO_A) $(OBJS)

clean : 
		rm -rf *.o *.a

fclean : clean
		rm -rf $(NAME)

re : fclean all