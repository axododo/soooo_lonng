NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror \
         -I. -I./MLX42/include -I./gnl

MLX = MLX42/build/libmlx42.a

SRC = main.c \
      gnl/get_next_line.c \
      gnl/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

LDFLAGS = -LMLX42/build -lmlx42 -lglfw -lm -ldl

all: $(NAME)

$(NAME): $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LDFLAGS) -o $(NAME)

$(MLX):
	@make -C MLX42

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make clean -C MLX42

fclean: clean
	rm -f $(NAME)
	@make fclean -C MLX42

re: fclean all

.PHONY: all clean fclean re
