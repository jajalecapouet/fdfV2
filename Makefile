NAME = fdf
SRCS =	src/get_next_line.c \
		src/get_next_line_utils \
		src/i_m_free.c \
		src/main.c \
		src/parsing_fill.c \
		src/parsing_fill_utils.c \
		src/parsing_fill_utils2.c \
		src/fdf.c
SRCS_TEST =	src/get_next_line.c \
			src/get_next_line_utils.c \
			src/i_m_free.c \
			src/main.c \
			src/parsing_fill.c \
			src/parsing_fill_utils.c \
			src/parsing_fill_utils2.c \
			src/test.c
OBJS_TEST = ${SRCS_TEST:.c=.o}
HEADERS = includes/fdf.h includes/libft.h includes/mlx.h includes/get_next_line.h
LIB = lib/libmlx.a lib/libft.a
RM = rm -f
CC = gcc
CFLAGS = -D BUFFER_SIZE=30
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	gcc -o ${NAME} ${OBJS} ${LIB} -framework OpenGL -framework AppKit

test: ${OBJS_TEST}
	gcc -o test ${OBJS_TEST} ${LIB} -framework OpenGL -framework AppKit

clean :
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

clean_test :
	${RM} ${OBJS_TEST}

fclean_test :	clean_test
	${RM} test

re : fclean all
