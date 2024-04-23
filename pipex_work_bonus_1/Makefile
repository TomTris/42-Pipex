NAME = pipex
CFLAGS = -Wall -Werror -Wextra
SRC =  pipex_man.c ft_create_man.c ft_i_1_or_last_man.c\
		pipex_bonus_2.c ft_create_bn1.c ft_create_bn2.c ft_execute_bn.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	cc $(CFLAGS) -o $(NAME) $(OBJS)  libft/libft.a 

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean:
	make fclean -C libft
	rm -f $(OBJS) $(NAME)

re: fclean all
