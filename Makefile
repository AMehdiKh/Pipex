NAME = pipex

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c

OBJS = ${SRCS:.c=.o}

LIBFT = /Users/ael-khel/Desktop/Pipex/LibFT/libft.a

.PHONY: clean
all: $(NAME)
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(LIBFT) $(OBJS) -o $@

$(LIBFT):
	$(MAKE) -C ./LibFT

clean:
	$(MAKE) fclean -C ./LibFT
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all