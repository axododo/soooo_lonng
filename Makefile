NAME = so_long
CC = cc
CFLAGS = -Werror -Wall -Wextra -g3 -I$(MLX)/includes 
MLX = MLX42/
PRINTF_DIR = ./printft
PRINTF = $(PRINTF_DIR)/libftprintf.a

SRC = map2.c \
			map.c \
      gnl/get_next_line.c \
      gnl/get_next_line_utils.c \
			libft.c \
			graphic.c \
			main.c \
			utils.c \
			graphic2.c \
			check_c.c

OBJ = $(SRC:.c=.o)

LDFLAGS = $(MLX)libmlx.so -lSDL2 -lm

MLX_REPO    = https://github.com/seekrs/MacroLibX.git
MLX_VERSION = f1e89ca

$(MLX_SO) :
	@git clone $(MLX_REPO) $(MLX_DIR)
	@git -C $(MLX_DIR) checkout $(MLX_VERSION) 2>/dev/null
	@make -C $(MLX_DIR) -j4

all: $(PRINTF) $(NAME)

$(NAME): $(MLX_SO) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_SO) $(PRINTF) $(LDFLAGS) -o $(NAME)

$(MLX):
	@make -C MLX42

$(PRINTF):
	@make -C $(PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(PRINTF_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make clean -C $(PRINTF_DIR)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re
