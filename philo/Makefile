
NAME			=	philo

SRCS			=	srcs/philo.c \
					srcs/init.c \
					srcs/miscellaneous.c \
					srcs/time.c \
					srcs/output.c \
					srcs/actions.c \
					srcs/forks.c \
					srcs/routine_monitor.c \
					srcs/conditions_of_running.c

OBJS			=	${SRCS:.c=.o}

HEAD			=	-I include

CC				=	clang

CFLAGS			=	-Wall -Werror -Wextra #-g3 -fsanitize=address

.c.o			:
					${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					${CC} ${CFLAGS} ${OBJS} -lpthread -o ${NAME}

all				:	${NAME}

clean			:
					@rm -rf ${OBJS}

fclean			:	clean
					@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re
