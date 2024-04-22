NAME = pipex
CFLAGS = -Wall -Werror -Wextra
SRC =  pipex.c ft_create.c ft_i_1_or_last.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	cc $(CFLAGS) -o $(NAME) $(OBJS)  libft/libft.a

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean:
	make clean -C libft
	rm -f $(OBJS) $(NAME)

re: fclean all