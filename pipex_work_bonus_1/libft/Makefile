CC = cc
CFLAGS = -Werror -Wextra -Werror
SRC = ft_printf.c ft_putc.c ft_putdi.c ft_putp.c ft_puts.c ft_putu.c ft_putx.c ft_putxx.c ft_strlen.c\
		ft_split.c ft_strjoin.c ft_strdup.c ft_strcpy.c\
		get_next_line.c get_next_line_utils.c
NAME = libft.a

OBJS = $(SRC:.c=.o)

$(NAME): all

all: $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS) $(NAME)

re: fclean all