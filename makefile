NAME = so_long
CC = cc
CFLAGS = -Werror -Wall -Wextra -g -I$(MLX)/includes -Ofast

MLX = MLX42/libmlx.so

SRC = main.c \
      gnl/get_next_line.c \
      gnl/get_next_line_utils.c \
			gui.c \
			libft.c


OBJ = $(SRC:.c=.o)

LDFLAGS = $(MLX) -lSDL2 -lm

all: $(NAME)

$(NAME): $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LDFLAGS) -o $(NAME)

$(MLX):
	@make -C MLX42

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
