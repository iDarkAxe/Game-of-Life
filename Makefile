.PHONY: all clean fclean re
CC = gcc
CFLAGS = -Wall -Wextra
CFLAGS_EXEC = -Wl,-strip-all
NAME = life

P_SRC = src/
P_OBJ = .obj/

SRC = \
	main.c \
	life.c \

SRCS =	\
	$(addprefix $(P_SRC), $(SRC))

OBJS = $(subst $(P_SRC), $(P_OBJ), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CFLAGS_EXEC) -o $@ $^

$(P_OBJ)%.o: $(P_SRC)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
