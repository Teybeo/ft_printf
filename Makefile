NAME = libftprintf.a

FILES += ft_printf.c
FILES += libft/array.c
FILES += libft/ft_strlen.c
FILES += libft/ft_memcpy.c
FILES += libft/ft_realloc.c
FILES += libft/ft_itoa.c
FILES += libft/ft_putchar_fd.c
FILES += libft/ft_putnbr_fd.c

OBJS = $(FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror

INCLUDES = -I libft/ -I .

LIBS = -lft -L libft

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

# $^ is the dependencies of the rule
# $@ is the name of the rule
%.o : %.c
	gcc $(FLAGS) $(INCLUDES) -o $@ -c $^

curqui: $(NAME)
	cp libftprintf.a ~/tools/curqui_test/
	make -C ~/tools/curqui_test/
	~/tools/curqui_test/ft_printf_tests

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all