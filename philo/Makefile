NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
INC_DIR = include

SRCS = $(SRC_DIR)/main.c \
	$(SRC_DIR)/parse.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/time.c \
	$(SRC_DIR)/state.c \
	$(SRC_DIR)/routine.c \
	$(SRC_DIR)/monitor.c \
	$(SRC_DIR)/simulation.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(INC_DIR)/philo.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
