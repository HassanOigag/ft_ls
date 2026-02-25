CC     = gcc
CFLAGS = -Wall -Wextra -Werror
NAME   = ft_ls
SRCS   = main.c
OBJS   = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): libft/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L libft -lft -o $(NAME)

libft/libft.a:
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -I libft -c $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
