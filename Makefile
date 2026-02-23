.PHONY: all clean fclean re
CC = cc
CFLAGS = -Wall -Wextra -g3
CFLAGS_EXEC = 
NAME = life

P_SRC = src/
P_OBJ = .obj/
P_GET_NEXT_LINE = get_next_line/
P_LIBFT = libft/

SRC = \
	main.c \
	life.c \
	life_utils.c \

INC = \
	life.h

LIBFT = $(P_LIBFT)libft.a
GET_NEXT_LINE = $(P_GET_NEXT_LINE)libgnl.a

SRCS =	\
	$(addprefix $(P_SRC), $(SRC))

INCS = \
	$(addprefix $(P_SRC), $(INC)) \
	$(addprefix $(P_LIBFT)/inc/, libft.h) \
	$(addprefix $(P_GET_NEXT_LINE), get_next_line.h) \

OBJS = $(subst $(P_SRC), $(P_OBJ), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(INCS) $(LIBFT) $(GET_NEXT_LINE)
	$(CC) $(CFLAGS) $(CFLAGS_EXEC) -o $@ $(OBJS) -L$(P_LIBFT) -lft -L$(P_GET_NEXT_LINE) -lgnl -L$(P_LIBFT) -lft

$(P_OBJ)%.o: $(P_SRC)%.c $(INCS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(P_SRC) -I $(P_GET_NEXT_LINE) -I $(P_LIBFT)inc

force:

$(LIBFT): force
	@$(MAKE) --no-print-directory -C $(P_LIBFT) all

$(GET_NEXT_LINE): force
	@$(MAKE) --no-print-directory -C $(P_GET_NEXT_LINE)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
