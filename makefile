NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g\
         -I. -I./MLX42/include -I./gnl

MLX = MLX42/build/libmlx42.a

SRC = main.c \
      gnl/get_next_line.c \
      gnl/get_next_line_utils.c \
			test.c \
			libft.c


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

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
