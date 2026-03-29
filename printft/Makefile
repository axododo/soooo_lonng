CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = libftprintf.a
HEADER = ft_printf.h
SRCS = ft_printf.c ft_putchar.c ft_putnbr.c ft_putstr.c ft_unsinbr.c ft_putnbrhexa.c ft_point.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar -crs $(NAME) $(OBJS)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
