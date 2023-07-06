SRC 	=	main.c \
			recursive.c \
			nonrecursive.c\
			findpath.c \
			common.c \
			die.c

OBJ			= ${SRC:.c=.o}

NAME		= mazegen
CC			= gcc -Wall -Wextra -Werror
RM			= rm -f

${NAME}:	${OBJ}
			${CC} ${OBJ} -o ${NAME}

all:		${NAME}

%.o:		%.c
			gcc -Werror -Wextra -Wall -c $< -o $@

clean:
			${RM} ${OBJ}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
